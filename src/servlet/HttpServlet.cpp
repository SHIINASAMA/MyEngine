/**
 * @file HttpServlet.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http Servlet 实现
 * @version 0.1
 */
#include <servlet/HttpServlet.h>

bool MyEngine::HttpServlet::service(HttpRequest *request, HttpResponse *response) {
    if (request->getMethod() == HttpMethod::GET) {
        init();
        doGet(request, response);
        destroy();
        return true;
    } else if (request->getMethod() == HttpMethod::POST) {
        init();
        doPost(request, response);
        destroy();
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
