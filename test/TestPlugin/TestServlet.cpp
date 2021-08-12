#include "TestServlet.h"


void TestServlet::doGet(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response) {
    response->setStateCode(302);
    response->setLocation("http://shiinasama.icu:8000/index.html");
}

void *Create() {
    return new TestServlet;
}
