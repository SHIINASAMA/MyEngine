/**
 * @file ServletContext.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Servlet 上下文类
 * @version 0.1
 */
#pragma once
#include <servlet/Servlet.h>

namespace MyEngine {

    /**
     * @brief Servlet 上下文
     */
    class ServletContext {
    public:
        typedef shared_ptr<ServletContext> Ptr;
        /**
         * 初始化一个 Servlet 上下文
         * @param servlet_name 服务名称
         * @param url URL
         * @param servlet Servlet 实例
         */
        ServletContext(const string &servlet_name, const string &url, const Servlet::Ptr &servlet) noexcept;
        /**
         * 默认析构函数
         */
        virtual ~ServletContext() noexcept = default;

        /**
         * 获取服务名称
         * @return 服务名称
         */
        string getName() const noexcept;
        /**
         * 获取 URL
         * @return URL
         */
        string getUrl() const noexcept;
        /**
         * 获取 Servlet 实例名称
         * @return Servlet 实例名称
         */
        string getServletClassName() const noexcept;
        /**
         * 获取 Servlet 实例
         * @return Servlet 实例
         */
        Servlet::Ptr getServlet() const noexcept;

        /**
         * Servlet 执行前
         * @deprecated 没有必要使用该函数
         */
        void servletInit() noexcept;
        /**
         * 执行服务
         * @param request 请求
         * @param response 回报
         * @deprecated 没有必要使用该函数
         */
        void servletService(const HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response) noexcept;
        /**
         * 执行后
         * @deprecated 没有必要使用该函数
         */
        void ServletDestroy() noexcept;

    private:
        string name;
        string url;
        Servlet::Ptr servlet{};
    };
}// namespace MyEngine