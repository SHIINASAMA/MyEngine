/**
 * @file NonsupportMethodServlet.h
 * @author kaoru
 * @date 2021.8.8
 * @brief 非法请求类（405）
 * @version 0.1
 */
#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine {

    /**
     * @brief 非法请求类
     */
    class NonsupportMethodServlet : public HttpServlet {
    public:
        bool service(HttpRequest *request, HttpResponse *response) override{
            response->setStateCode(405);
            response->setHeader(new HttpHeader {"Access-Control-Allow-Methods", "GET, POST"});
            response->setServer("My Engine");
            return true;
        }
    };
}

