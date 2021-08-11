#include "TestServlet.h"


void TestServlet::doGet(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response) {
    auto v = request->getHeader("key");
    response->setHeader(v);
}

void *Create() {
    return new TestServlet;
}
