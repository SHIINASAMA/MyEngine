#include <cerrno>
#include <cstring>
#include <http/HttpServer.h>
#include <http/HttpParser.h>
#include <sstream>

using MyEngine::HttpServer;
using MyEngine::HttpHeader;
using MyEngine::HttpResponse;
using MyEngine::HttpRequest;
using MyEngine::HttpHeader;
using MyEngine::HttpParser;

int main(){
    HttpServer server("0.0.0.0", 8000);
    bool is_init = server.init(20);
    if(!is_init){
        printf("%s\n", strerror(errno));
        return errno;
    }
    printf("server start\n");
    auto client = server.accept();

    HttpRequest request;
    HttpParser::RequestParser(client, &request);
    for(const auto& i : request.getHeaders()){
        printf("%s: %s\n", i.key.c_str(), i.value.c_str());
    }
    if(request.getMethod() == MyEngine::HttpMethod::POST){
        printf("%s", request.getBody().c_str());
    }

    MyEngine::HttpResponse response(11, 302);
    response.setHeader({"Location", "https://www.baidu.com"});
    response.setHeader({"Server","MyEngine HttpServer"});
    response.setHeader({"Host", "localhost:8080"});
    auto basicString = response.dump().str();
    auto send_len = client.send(basicString.c_str(), basicString.length(), 0);
    client.close();
    return 0;
}