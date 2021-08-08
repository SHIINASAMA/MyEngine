#include <servlet/HttpServlet.h>

bool MyEngine::HttpServlet::service(HttpRequest *request, HttpResponse *response) {
    if (request->getMethod() == HttpMethod::GET) {
        doGet(request, response);
        return true;
    } else if (request->getMethod() == HttpMethod::POST) {
        doPost(request, response);
        return true;
    } else {
        // DO NOTTING...
        return false;
    }
}

void MyEngine::HttpServlet::init() {
}

void MyEngine::HttpServlet::destroy() {
}

void MyEngine::HttpServlet::doGet(MyEngine::HttpRequest *request, MyEngine::HttpResponse *response) {
    response->setStateCode(200);
    response->setServer("My Engine");
}

void MyEngine::HttpServlet::doPost(MyEngine::HttpRequest *request, MyEngine::HttpResponse *response) {
    response->setStateCode(200);
    response->setServer("My Engine");
}
