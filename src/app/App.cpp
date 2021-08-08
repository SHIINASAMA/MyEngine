#include <app/App.h>
#include <app/NonsupportMethodServlet.h>
#include <app/NotFindServlet.h>
#include <app/SuccessServlet.h>
#include <app/ErrorServlet.h>
#include <filesystem>
#include <fstream>
#include <http/HttpParser.h>
#include <servlet/HttpServlet.h>
#include <thread>

MyEngine::NotFindServlet notFindServlet;
MyEngine::NonsupportMethodServlet nonsupportMethodServlet;
MyEngine::SuccessServlet successServlet;
MyEngine::ErrorServlet errorServlet;

MyEngine::App *MyEngine::App::app;

void MyEngine::App::CreateApp(const string &ipaddress, unsigned int port) {
    if (!app) {
        app = new App(ipaddress, port);
    }
}

MyEngine::App *MyEngine::App::GetApp() {
    return app;
}

MyEngine::App::App(const string &ipaddress, unsigned short port) : HttpServer(ipaddress, port) {
}

MyEngine::App::~App() {
    delete app;
}

void MyEngine::App::regServlet(const string &servlet_name, const string &url, MyEngine::Servlet *servlet) {
    auto config = ServletContext(servlet_name, url, servlet);
    servletMap.emplace(url, config);
}

[[noreturn]] void MyEngine::App::exec() {
    this->init(10);
    while (true) {
        auto client = this->accept();
        if (client.good()) {
            auto worker = new TcpThread(client);
            std::thread thread(&TcpThread::Main, worker);
            thread.detach();
        }
    }
}

const std::map<string, MyEngine::ServletContext, MyEngine::strcmp<>> &MyEngine::App::getMap() const {
    return this->servletMap;
}

MyEngine::TcpThread::TcpThread(TcpClient client) {
    this->client = client;
}

void MyEngine::TcpThread::Main() {
    HttpRequest request;
    HttpResponse response;
    if (!HttpParser::RequestParser(client, &request)) {
        client.close();
        return;
    }

    auto app             = App::GetApp();
    auto servletMap      = app->getMap();
    auto servlet_context = servletMap.find(request.getUrl());
    if (servlet_context != servletMap.end()) {
        auto servlet     = dynamic_cast<const HttpServlet *>(servlet_context->second.getServlet());
        auto raw_servlet = const_cast<HttpServlet *>(servlet);
        if (raw_servlet->service(&request, &response)) {
            auto baseString = response.dump().str();
            client.send(baseString.c_str(), baseString.length(), 0);
        } else {
            // 不支持的方法 - 405
            nonsupportMethodServlet.service(&request, &response);
            auto baseString = response.dump().str();
            client.send(baseString.c_str(), baseString.length(), 0);
        }
    } else {
        // 查找本地资源
        string raw_url = std::filesystem::current_path();
        raw_url.append(request.getUrl());
        if (std::filesystem::exists(raw_url)) {
            // 发送文件
            std::ifstream file;
            file.open(raw_url, std::fstream::out | std::fstream::binary);
            if (file.good()) {
                file.seekg(0, std::ifstream::end);
                ssize_t file_len = file.tellg();

                successServlet.service(&request, &response);
                response.setContentLength(file_len);
                auto baseString = response.dump().str();
                client.send(baseString.c_str(), baseString.length(), 0);

                file.clear();
                file.seekg(0, std::ios::beg);
                char buffer[1024];
                ssize_t len;
                while (true) {
                    file.read(buffer, 1024);
                    len = file.gcount();
                    if(len == 0){
                        break;
                    }
                    client.send(buffer, len, 0);
                }
            }else{
                // 服务器内部错误 - 500
                errorServlet.service(&request, &response);
                auto baseString = response.dump().str();
                client.send(baseString.c_str(), baseString.length(), 0);
            }
        } else {
            // 未查找到资源 - 404
            notFindServlet.service(&request, &response);
            auto baseString = response.dump().str();
            client.send(baseString.c_str(), baseString.length(), 0);
        }
    }
    client.close();
    delete this;
}
