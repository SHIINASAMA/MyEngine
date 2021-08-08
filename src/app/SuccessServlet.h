#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine{

    class SuccessServlet : public HttpServlet{
    public:
        bool service(HttpRequest *request, HttpResponse *response) override{
            return HttpServlet::service(request, response);
        }
    };
}