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
        bool service(const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) override {
            response->setStateCode(500);
            response->setServer("My Engine");
            response->setHeader(make_shared<HttpHeaderElement>("error", strerror(errno)));
            return true;
        }
    };
}// namespace MyEngine
