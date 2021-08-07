#pragma once
#include <http/Http.h>

namespace MyEngine{

    class HttpClient{
    public:
        static bool Get(const string &ipaddress, unsigned short port, HttpRequest &request, HttpResponse *response);
        static bool Post(const string &ipaddress, unsigned short port, HttpRequest &request, HttpResponse *response);
    };
}