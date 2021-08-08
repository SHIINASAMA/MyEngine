/**
 * @file NotFindServlet.h
 * @author kaoru
 * @date 2021.8.8
 * @brief 资源非法类（404）
 * @version 0.1
 */
#pragma once
#include <servlet/HttpServlet.h>

namespace MyEngine {

    /**
     * @brief 资源非法类
     */
    class NotFindServlet : public HttpServlet {
    public:
        bool service(HttpRequest *request, HttpResponse *response) override{
            response->setStateCode(404);
            response->setServer("My Engine");
            return true;
        }
    };
}// namespace MyEngine
