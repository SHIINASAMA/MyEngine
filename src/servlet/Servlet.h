#pragma once
#include <http/Http.h>

namespace MyEngine{

    class Servlet {
    public:
        Servlet() = default;
        virtual ~Servlet() = default;

        virtual void init() = 0;
        virtual bool service(HttpRequest *request, HttpResponse *response) = 0;
        virtual void destroy() = 0;

        std::string getClassName() const;
    };
}