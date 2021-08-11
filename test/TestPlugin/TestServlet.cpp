#include "TestServlet.h"


void TestServlet::doGet(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response) {
    response->setStateCode(302);
    response->setLocation("https://www.baidu.com");
}

void *Create() {
    return new TestServlet;
}
