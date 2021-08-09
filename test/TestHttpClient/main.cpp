#include <cstring>
#include <http/HttpClient.h>

using namespace MyEngine;

int main() {
    HttpRequest::Ptr request;
    request->setUrl("/");
    request->setHeader(MAKE_ELEMENT("Client", "MyEngine TestClient"));
    HttpResponse::Ptr response;
    //    if(!HttpClient::Get("121.196.103.114", 8000, request, &response)){
    if (!HttpClient::Post("220.181.38.251", 80, request, response)) {
        printf("%s", strerror(errno));
        return errno;
    }
    for (const auto &i : response->getElements()) {
        printf("%s : %s\n", i.second->key.c_str(), i.second->value.c_str());
    }
    printf("%s", response->getBody().c_str());
    return 0;
}