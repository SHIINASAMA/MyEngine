/**
 * @file SuccessServlet.h
 * @author kaoru
 * @date 2021.8.8
 * @brief 请求成功类（200）
 * @version 0.1
 */
#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine{

    /**
     * @brief 请求成功类
     */
    class SuccessServlet : public HttpServlet{
    public:
        bool service(HttpRequest *request, HttpResponse *response) override{
            return HttpServlet::service(request, response);
        }
    };
}