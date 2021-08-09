#include <http/HttpParser.h>
#include <http/HttpRequest.h>
#include <http/HttpServer.h>
#include <pthread.h>
#include <servlet/Servlet.h>
#include <sstream>

using namespace MyEngine;

class MyServlet : Servlet {
public:
    void init() override {}
    bool service(const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) override {
        string url   = request->getUrl();
        string query = request->getQueryString();
        string body  = "Your request url is \"" + url + "\", Your request query string is \"" + query + "\"";
        response->setBody(body);
        response->setHeader(make_shared<HttpHeaderElement>("content-length", std::to_string(body.length())));
        return true;
    }
    void destroy() override {}
};

void *exec(void *client) {
    auto tcpClient = (TcpClient::Ptr *) &client;
    HttpRequest::Ptr request;
    HttpResponse::Ptr response;
    HttpParser::RequestParser(*tcpClient, request);
    MyServlet servlet{};
    servlet.service(request, response);
    auto baseString = response->dump();
    (*tcpClient)->send(baseString.c_str(), baseString.length(), 0);
    (*tcpClient)->close();
    return nullptr;
}

int main() {
    HttpServer server("0.0.0.0", 80);
    bool is_init = server.init(20);
    if (!is_init) {
        printf("%s\n", strerror(errno));
        return errno;
    }
    printf("server start\n");
    auto client = server.accept();
    pthread_t thread;
    pthread_create(&thread, nullptr, exec, (void *) &client);
    pthread_join(thread, nullptr);
    printf("thread exit\n");
    server.shutdown();
    return 0;
}