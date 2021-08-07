#pragma once
#include <servlet/Servlet.h>

namespace MyEngine {

    class HttpServlet : public Servlet {
    public:
        void init() override;
        void service(HttpRequest *request, HttpResponse *response) override;
        void destroy() override;

        virtual void doGet(HttpRequest *request, HttpResponse *response);
        virtual void doPost(HttpRequest *request, HttpResponse *response);
    };
}// namespace MyEngine