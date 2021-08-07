#include <http/Http.h>
#include <http/HttpParser.h>
#include <http/HttpServer.h>
#include <pthread.h>
#include <servlet/Servlet.h>
#include <sstream>

using namespace MyEngine;

class MyServlet : Servlet {
public:
    void init() override {}
    void service(HttpRequest &request, HttpResponse &response) override {
        string url   = request.getUrl();
        string query = request.getQueryString();
        string body  = "Your request url is \"" + url + "\", Your request query string is \"" + query + "\"";
        response.setBody(body);
        response.setHeader({"content-length", std::to_string(body.length())});
    }
    void destroy() override {}
};

void *exec(void *client) {
    auto *tcpClient = (TcpClient *) client;
    HttpRequest request;
    HttpResponse response;
    HttpParser::RequestParser(*tcpClient, &request);
    MyServlet servlet;
    servlet.service(request, response);
    auto baseString = response.dump().str();
    tcpClient->send(baseString.c_str(), baseString.length(), 0);
    tcpClient->close();
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