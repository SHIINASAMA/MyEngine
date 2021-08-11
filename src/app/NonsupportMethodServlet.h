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
        bool service(const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) override {
            response->setStateCode(405);
            response->setHeader(make_shared<HttpHeaderElement>("Access-Control-Allow-Methods", "GET, POST"));
            return true;
        }
    };
}// namespace MyEngine
