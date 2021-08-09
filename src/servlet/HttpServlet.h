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
         * @brief 智能指针对象
         */
        typedef shared_ptr<HttpServlet> Ptr;

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
        bool service(const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) override;
        /**
         * 执行后
         */
        void destroy() override;

        /**
         * 执行 Get 请求
         * @param request 请求
         * @param response 回报
         */
        virtual void doGet(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response);
        /**
         * 执行 Post 请求
         * @param request 请求
         * @param response 回报
         */
        virtual void doPost(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response);
    };
}// namespace MyEngine