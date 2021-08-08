#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine {

    class NotFindServlet : public HttpServlet {
    public:
        bool service(HttpRequest *request, HttpResponse *response) override{
            response->setStateCode(404);
            response->setServer("My Engine");
            return true;
        }
    };
}// namespace MyEngine
