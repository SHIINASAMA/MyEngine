#pragma once
#include <http/Http.h>

namespace MyEngine{

    class Servlet{
    public:
        Servlet() = default;
        virtual void service(HttpRequest &request, HttpResponse &response);
        virtual ~Servlet() = default;

        string getClassName() const;
    };
}