/**
 * @file App.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief 应用程序类实现
 * @version 0.1
 */

#include <Utility.h>
#include <app/App.h>
#include <app/ErrorServlet.h>
#include <app/NonsupportMethodServlet.h>
#include <app/NotFindServlet.h>
#include <app/SuccessServlet.h>
#include <filesystem>
#include <fstream>
#include <http/HttpParser.h>
#include <servlet/HttpServlet.h>

MyEngine::NotFindServlet notFindServlet;
MyEngine::NonsupportMethodServlet nonsupportMethodServlet;
MyEngine::SuccessServlet successServlet;
MyEngine::ErrorServlet errorServlet;

MyEngine::App *MyEngine::App::app;

using namespace MyEngine;

bool IsFileExistent(const std::filesystem::path &path) {
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

static void Main(const TcpClient::Ptr &client) {
    //    LOG_INFO("接入连接");
    auto request  = make_shared<HttpRequest>();
    auto response = make_shared<HttpResponse>();
    if (!HttpParser::RequestParser(client, request)) {
        client->close();
        return;
    }

    auto app        = App::GetApp();
    auto servletMap = app->getMap();
    response->setServer(app->getServerName());
    auto servlet_context = servletMap.find(request->getUrl());
    if (servlet_context != servletMap.end()) {
        auto servlet = servlet_context->second.getServlet();
        if (servlet->service(request, response)) {
            LOG_INFO("请求Servlet -> (friendly_name)%s - %s\n", servlet_context->second.getName().c_str(), servlet_context->second.getServletClassName().c_str());
            auto baseString = response->dump();
            client->send(baseString.c_str(), baseString.length(), 0);
        } else {
            // 不支持的方法 - 405
            LOG_INFO("不支持的Http方法");
            nonsupportMethodServlet.service(request, response);
            auto baseString = response->dump();
            client->send(baseString.c_str(), baseString.length(), 0);
        }
    } else {
        // 查找本地资源
        string raw_url = std::filesystem::current_path();
        raw_url += app->getWebDir() + request->getUrl();
        if (IsFileExistent(raw_url)) {
            LOG_INFO("请求资源 -> %s", raw_url.c_str());
            // 发送文件
            std::ifstream file;
            file.open(raw_url, std::fstream::out | std::fstream::binary);
            if (file.good()) {
                file.seekg(0, std::ifstream::end);
                ssize_t file_len = file.tellg();

                successServlet.service(request, response);
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
                    if (len == 0) {
                        break;
                    }
                    client->send(buffer, len, 0);
                }
            } else {
                // 服务器内部错误 - 500
                LOG_WARN("服务器内部错误-505 -> %s", raw_url.c_str());
                errorServlet.service(request, response);
                auto baseString = response->dump();
                client->send(baseString.c_str(), baseString.length(), 0);
            }
        } else {
            // 未查找到资源 - 404
            LOG_WARN("请求资源不存在-404 -> %s", raw_url.c_str());
            notFindServlet.service(request, response);
            auto baseString = response->dump();
            client->send(baseString.c_str(), baseString.length(), 0);
        }
    }
    client->close();
}

MyEngine::App::App(const ServerConfig::Ptr &config)
    : HttpServer(config->ipaddress, config->port), serverConfig(config) {
    this->pool = new ThreadPool(config->threadPoolConfig.name, config->threadPoolConfig.threads);
    pthread_rwlock_init(&this->lock, nullptr);
    LOG_INFO("服务器 - \"%s\" 启动, Listen {%s:%d}", config->name.c_str(), config->ipaddress.c_str(), config->port);
}

MyEngine::App *MyEngine::App::GetApp() {
    return app;
}


void MyEngine::App::regServlet(const string &servlet_name, const string &url, const Servlet::Ptr &servlet) {
    auto config = ServletContext(servlet_name, url, servlet);
    servletMap.emplace(url, config);
}

void MyEngine::App::exec() {
    this->init(10);
    while (!this->isShutdown) {
        auto client = this->accept();
        if (client->good()) {
            pool->execute(Main, client);
        }
    }
}

const std::map<string, MyEngine::ServletContext, MyEngine::strcmp<>> &MyEngine::App::getMap() const {
    return this->servletMap;
}

MyEngine::App::~App() {
    this->isShutdown = true;
    HttpServer::shutdown();
    pool->shutdown();
    pthread_rwlock_destroy(&this->lock);
}

void App::shutdown() {
    this->isShutdown = true;
    HttpServer::shutdown();
    pool->shutdown();
}

void App::start() {
    std::thread(&App::exec, this).detach();
}

void App::CreateApp(const ServerConfig::Ptr &config) {
    if (!app) {
        app = new App(config);
        app->reload();
    }
}

void App::reload() {
    LOG_INFO("开始重载插件");
    pthread_rwlock_rdlock(&this->lock);
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
    LOG_INFO("插件重载完成")
}
