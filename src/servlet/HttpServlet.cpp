#include <servlet/HttpServlet.h>

void MyEngine::HttpServlet::service(HttpRequest *request, HttpResponse *response) {
    if (request->getMethod() == HttpMethod::GET) {
        doGet(request, response);
    } else if (request->getMethod() == HttpMethod::POST) {
        doPost(request, response);
    } else {
        // DO NOTTING...
    }
}

void MyEngine::HttpServlet::init() {
}

void MyEngine::HttpServlet::destroy() {
}

void MyEngine::HttpServlet::doGet(MyEngine::HttpRequest *request, MyEngine::HttpResponse *response) {
}

void MyEngine::HttpServlet::doPost(MyEngine::HttpRequest *request, MyEngine::HttpResponse *response) {
}
