#include <cerrno>
#include <cstring>
#include <http/HttpParser.h>
#include <http/HttpServer.h>
#include <sstream>

using MyEngine::HttpHeader;
using MyEngine::HttpParser;
using MyEngine::HttpRequest;
using MyEngine::HttpResponse;
using MyEngine::HttpServer;

int main() {
    HttpServer server("0.0.0.0", 80);
    bool is_init = server.init(20);
    if (!is_init) {
        printf("%s\n", strerror(errno));
        return errno;
    }
    printf("server start\n");

    auto client = server.accept();

    HttpRequest::Ptr request;
    HttpParser::RequestParser(client, request);
    for (const auto &i : request->getElements()) {
        printf("%s: %s\n", i.second->key.c_str(), i.second->value.c_str());
    }
    if (request->getMethod() == MyEngine::HttpMethod::POST) {
        printf("%s", request->getBody().c_str());
    }

    MyEngine::HttpResponse response(11, 200);
    response.setHeader(MAKE_ELEMENT("Server", "MyEngine HttpServer"));
    response.setHeader(MAKE_ELEMENT("Host", "localhost:8080"));
    auto basicString = response.dump();
    auto send_len    = client->send(basicString.c_str(), basicString.length(), 0);
    client->close();

    return 0;
}