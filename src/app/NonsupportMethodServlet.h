#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine {

    class NonsupportMethodServlet : HttpServlet {
    public:
        bool service(HttpRequest *request, HttpResponse *response) override{
            response->setStateCode(405);
            response->setHeader(new HttpHeader {"Access-Control-Allow-Methods", "GET, POST"});
            response->setServer("My Engine");
            return true;
        }
    };
}

