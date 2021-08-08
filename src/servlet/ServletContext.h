/**
 * @file ServletContext.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Servlet 上下文类
 * @version 0.1
 */
#pragma once
#include <servlet/Servlet.h>

namespace MyEngine{

    /**
     * @brief Servlet 上下文
     */
    class ServletContext {
    public:
        /**
         * 初始化一个 Servlet 上下文
         * @param servlet_name 服务名称
         * @param url URL
         * @param servlet Servlet 实例
         */
        ServletContext(const string &servlet_name, const string &url, Servlet *servlet);
        /**
         * 默认析构函数
         */
        virtual ~ServletContext();

        /**
         * 获取服务名称
         * @return 服务名称
         */
        string getName() const;
        /**
         * 获取 URL
         * @return URL
         */
        string getUrl() const;
        /**
         * 获取 Servlet 实例名称
         * @return Servlet 实例名称
         */
        string getServletClassName() const;
        /**
         * 获取 Servlet 实例
         * @return Servlet 实例
         */
        const Servlet *getServlet() const;

        /**
         * Servlet 执行前
         * @deprecated 没有必要使用该函数
         */
        void servletInit();
        /**
         * 执行服务
         * @param request 请求
         * @param response 回报
         * @deprecated 没有必要使用该函数
         */
        void servletService(HttpRequest *request, HttpResponse *response);
        /**
         * 执行后
         * @deprecated 没有必要使用该函数
         */
        void ServletDestroy();

    private:
        string name;
        string url;
        Servlet *servlet;
    };
}