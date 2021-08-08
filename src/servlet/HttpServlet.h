/**
 * @file HttpServlet.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http Servlet 类
 * @version 0.1
 */
#pragma once
#include <servlet/Servlet.h>

namespace MyEngine {

    /**
     * @brief Http Servlet 类
     */
    class HttpServlet : public Servlet {
    public:
        /**
         * 执行前
         */
        void init() override;
        /**
         * 执行服务
         * @param request 请求
         * @param response 回报
         * @return 是否执行成功
         */
        bool service(HttpRequest *request, HttpResponse *response) override;
        /**
         * 执行后
         */
        void destroy() override;

        /**
         * 执行 Get 请求
         * @param request 请求
         * @param response 回报
         */
        virtual void doGet(HttpRequest *request, HttpResponse *response);
        /**
         * 执行 Post 请求
         * @param request 请求
         * @param response 回报
         */
        virtual void doPost(HttpRequest *request, HttpResponse *response);
    };
}// namespace MyEngine