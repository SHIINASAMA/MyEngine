#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine {

    class ErrorServlet : public HttpServlet {
    public:
        bool service(HttpRequest *request, HttpResponse *response) override {
            response->setStateCode(500);
            response->setServer("My Engine");
            response->setHeader(new HttpHeader{"error", strerror(errno)});
            return true;
        }
    };
}// namespace MyEngine
