/**
 * @file App.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief 应用程序类实现
 * @version 0.1
 */

#include <Utility.h>
#include <app/App.h>
#include <csignal>
#include <fcntl.h>
#include <filesystem>
#include <fstream>
#include <http/HttpParser.h>
#include <servlet/HttpServlet.h>
#include <sys/stat.h>

MyEngine::App::Ptr MyEngine::App::app;

using namespace MyEngine;

static thread_local std::atomic_bool isBreak;

static void onSIGPIPE(int code) {
    isBreak = true;
}

static bool IsFileExistent(const std::filesystem::path &path) {
    std::error_code error;
    auto file_status = std::filesystem::status(path, error);
    if (error) {
        return false;
    }
    if (!std::filesystem::exists(file_status)) {
        return false;
    }
    if (std::filesystem::is_directory(file_status)) {
        return false;
    }
    return true;
}

static void on404(const TcpClient::Ptr &client, const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) {
    LOG_WARN("请求资源不存在-404 -> %s", request->getUrl().c_str());
    response->setStateCode(404);
    auto baseString = response->dump();
    client->send(baseString.c_str(), baseString.length(), 0);
}

static void on405(const TcpClient::Ptr &client, const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) {
    LOG_INFO("不支持的Http方法");
    response->setStateCode(405);
    response->setHeader(MAKE_ELEMENT("Access-Control-Allow-Methods", "GET, POST"));
    auto baseString = response->dump();
    client->send(baseString.c_str(), baseString.length(), 0);
}

static void on416(const TcpClient::Ptr &client, const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) {
    LOG_INFO("错误的文件区间");
    response->setStateCode(416);
    auto baseString = response->dump();
    client->send(baseString.c_str(), baseString.length(), 0);
}

static void on500(const TcpClient::Ptr &client, const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) {
    LOG_WARN("服务器内部错误-500 -> %s", request->getUrl().c_str());
    response->setStateCode(500);
    response->setHeader(MAKE_ELEMENT("error", strerror(errno)));
    auto baseString = response->dump();
    client->send(baseString.c_str(), baseString.length(), 0);
}

static void on200(const TcpClient::Ptr &client, const HttpRequest::Ptr &request, const HttpResponse::Ptr &response, const string &fileName) {
    std::ifstream file;
    struct stat buffer{0};
    stat(fileName.c_str(), &buffer);
    response->setLastModified(buffer.st_mtime);
    file.open(fileName.c_str(), std::fstream::out | std::fstream::binary);
    if (file.good()) {
        LOG_INFO("请求完整资源 -> %s", fileName.c_str());
        file.seekg(0, std::ifstream::end);
        ssize_t file_len = file.tellg();
        response->setStateCode(200);
        response->setContentLength(file_len);
        auto baseString = response->dump();
        client->send(baseString.c_str(), baseString.length(), 0);

        file.clear();
        file.seekg(0, std::ios::beg);
        char buffer[1024];
        ssize_t len;
        while (true) {
            file.read(buffer, 1024);
            len = file.gcount();
            if (len <= 0 || isBreak) {
                break;
            }
            client->send(buffer, len, 0);
            sleep(0);
        }
    } else {
        on500(client, request, response);
    }
}

static void on206(const TcpClient::Ptr &client, const HttpRequest::Ptr &request, const HttpResponse::Ptr &response, const string &fileName, const HttpRange::Ptr &ranges) {
    std::ifstream file;
    struct stat buffer{0};
    stat(fileName.c_str(), &buffer);
    response->setLastModified(buffer.st_mtime);
    file.open(fileName, std::fstream::out | std::fstream::binary);
    if (file.good()) {
        file.seekg(0, std::ifstream::end);
        ssize_t fileLen = file.tellg();
        file.clear();

        // 校验 Range 字段并顺带计算 Content-Length 字段的值
        ssize_t contentLength = 0;
        auto allRanges        = ranges->getRanges();
        for (auto &range : allRanges) {
            if (range.first < 0) range.first = 0;
            if (range.second < 0) range.second = fileLen - 1;

            if (range.first > range.second || range.second > fileLen) {
                file.close();
                on416(client, request, response);
                goto end;
            }

            contentLength += range.second - range.first;
        }

        // 回应文件块
        bool isFirst = true;
        for (auto range : allRanges) {
            LOG_INFO("请求分块资源 -> %s [%ld, %ld]", fileName.c_str(), range.first, range.second);
            ssize_t sendCount = range.second - range.first;
            if (isFirst) {
                isFirst = false;
                response->setStateCode(206);
                response->setContentLength(contentLength);
                response->setContentRange(range.first, range.second, fileLen);
                auto baseString = response->dump();
                client->send(baseString.c_str(), baseString.length(), 0);
            } else {
                string tempResponse{0};
                tempResponse += "Content-Range: " + HttpRange::MakeContentRange(range.first, range.second, fileLen) + "\r\n\r\n";
                client->send(tempResponse.c_str(), tempResponse.length(), 0);
            }

            file.clear();
            file.seekg(range.first, std::ios::beg);
            char buffer[1024];
            while (sendCount) {
                if (sendCount > 1024) {
                    file.read(buffer, 1024);
                    auto l = client->send(buffer, 1024, 0);
                    if (l == -1) {
                        break;
                    }
                    sendCount -= l;
                } else {
                    file.read(buffer, sendCount);
                    auto l = client->send(buffer, sendCount, 0);
                    if (l == -1) {
                        break;
                    }
                    sendCount -= l;
                }
                sleep(0);
            }
        }
        file.close();
    } else {
        on500(client, request, response);
    }
end:;
}

static void Main(const TcpClient::Ptr &client) {
    auto request  = make_shared<HttpRequest>();
    auto response = make_shared<HttpResponse>();
    time_t t;
    time(&t);
    response->setDate(t);
    response->setHeader(MAKE_ELEMENT("Accept-Ranges", "bytes"));
    response->setConnection("close");

    if (!HttpParser::RequestParser(client, request)) {
        client->close();
        return;
    }

    auto app            = App::GetApp();
    auto servletContext = app->findServletContextByUrl(request->getUrl());
    response->setServer(app->getServerName());
    if (servletContext) {
        auto servlet = servletContext->getServlet();
        if (servlet->service(request, response)) {
            LOG_INFO("请求Servlet -> (friendly_name)%s - %s\n", servletContext->getName().c_str(), servletContext->getServletClassName().c_str());
            auto baseString = response->dump();
            client->send(baseString.c_str(), baseString.length(), 0);
        } else {
            on405(client, request, response);
        }
    } else {
        // 查找本地资源
        isBreak = false;
        signal(SIGPIPE, onSIGPIPE);
        string raw_url = std::filesystem::current_path();
        raw_url += app->getWebDir() + request->getUrl();
        if (IsFileExistent(raw_url)) {
            auto ranges = request->getRange();
            if (ranges) {
                on206(client, request, response, raw_url, ranges);
            } else {
                on200(client, request, response, raw_url);
            }
        } else {
            on404(client, request, response);
        }
    }
    client->close();
}

MyEngine::App::App(const ServerConfig::Ptr &config)
    : HttpServer(config->baseInfo.ipaddress, config->baseInfo.port), serverConfig(config) {
    auto fd   = this->getSocket();
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    this->pool = make_shared<ThreadPool>(config->threadPoolConfig.name, config->threadPoolConfig.threads);
    pthread_rwlock_init(&this->lock, nullptr);
    LOG_INFO("服务器 - \"%s\" 启动, Listen {%s:%d}", config->baseInfo.name.c_str(), config->baseInfo.ipaddress.c_str(), config->baseInfo.port);
}

MyEngine::App::Ptr MyEngine::App::GetApp() {
    return app;
}

void MyEngine::App::regServlet(const string &servlet_name, const string &url, const Servlet::Ptr &servlet) {
    auto config = make_shared<ServletContext>(servlet_name, url, servlet);
    servletMap.emplace(url, config);
}

void MyEngine::App::exec() {
    this->init(10);
    while (!this->isShutdown) {
        auto client = this->accept();
        if (client->good()) {
            pool->execute(Main, client);
        }
        sleep(0);
    }
}

MyEngine::App::~App() {
    this->isShutdown = true;
    HttpServer::shutdown();
    pool->shutdown();
    pthread_rwlock_destroy(&this->lock);
}

void App::shutdown() {
    this->isShutdown = true;
    Socket::shutdown(SHUT_RDWR);
    background->join();
    HttpServer::shutdown();
    pool->shutdown();
}

void App::start() {
    this->background = std::make_shared<std::thread>(&App::exec, this);
}

void App::CreateApp(const ServerConfig::Ptr &config) {
    if (!app) {
        app = shared_ptr<App>(new App(config));
        app->reload();
    }
}

void App::reload() {
    pthread_rwlock_wrlock(&this->lock);
    this->servletMap.clear();
    this->plugins.clear();
    string raw_url = std::filesystem::current_path().string() + app->getPluginDir();
    for (const auto &file : std::filesystem::directory_iterator(raw_url)) {
        auto file_name = file.path();
        auto plugin    = make_shared<Plugin>(file_name);
        if (!plugin->open()) {
            LOG_WARN("插件文件 %s 无效", file_name.c_str());
            continue;
        }

        auto manifest = plugin->getManifest();
        if (!manifest) {
            LOG_WARN("插件文件 %s 未携带清单信息", file_name.c_str());
            continue;
        }

        if (!manifest->entry) {
            LOG_WARN("插件文件 %s 入口信息无效", file_name.c_str());
            continue;
        }

        auto p = (HttpServlet *) manifest->entry();
        if (!p) {
            LOG_WARN("插件文件 %s 入口函数错误", file_name.c_str());
            continue;
        }
        auto servlet = shared_ptr<HttpServlet>(p);
        this->regServlet(manifest->name, manifest->url, servlet);
        this->plugins.push_back(plugin);
        LOG_INFO("载入插件 %s\33[1;32m[%s:v%d -> %s]\33[0m 成功", file_name.c_str(), manifest->name, manifest->version, manifest->url);
    }
    pthread_rwlock_unlock(&this->lock);
}

ServletContext::Ptr App::findServletContextByUrl(const string &url) {
    ServletContext::Ptr res;
    pthread_rwlock_rdlock(&this->lock);
    auto context = servletMap.find(url);
    if (context != servletMap.end()) {
        res = context->second;
    } else {
        res = nullptr;
    }
    pthread_rwlock_unlock(&this->lock);
    return res;
}