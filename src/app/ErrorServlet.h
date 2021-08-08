/**
 * @file ErrorServlet.h
 * @author kaoru
 * @date 2021.8.8
 * @brief 服务器内部错误类（500）
 * @version 0.1
 */
#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine {

    /**
     * @brief 服务器内部错误类
     */
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
