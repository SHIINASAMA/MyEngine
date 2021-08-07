#include <app/App.h>
#include <http/HttpParser.h>
#include <servlet/HttpServlet.h>

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
        App::onRequest(client);
    }
}

auto MyEngine::App::getMap() const {
    return this->servletMap;
}

void *MyEngine::App::onRequest(MyEngine::TcpClient client) {
    HttpRequest request;
    HttpResponse response;
    if (!HttpParser::RequestParser(client, &request)) {
        return nullptr;
    }

    auto servlet_context = servletMap.find(request.getUrl());
    if (servlet_context != servletMap.end()) {
        auto servlet     = dynamic_cast<const HttpServlet *>(servlet_context->second.getServlet());
        auto raw_servlet = const_cast<HttpServlet *>(servlet);
        printf("%s : %s\n", servlet_context->second.getName().c_str() ,raw_servlet->getClassName().c_str());
        raw_servlet->service(&request, &response);
        auto baseString = response.dump().str();
        client.send(baseString.c_str(), baseString.length(), 0);
        client.close();
    } else {
        // 不存在 servlet

        // 查找本地资源

        // 404
    }
    return nullptr;
}
