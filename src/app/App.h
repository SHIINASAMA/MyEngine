/**
 * @file App.h
 * @author kaoru
 * @date 2021.8.8
 * @brief 应用程序类
 * @version 0.1
 */
#pragma once
#include <http/HttpServer.h>
#include <servlet/ServletContext.h>
#include <thread/ThreadPool.h>
#include <atomic>

namespace MyEngine {

    /**
     * @brief 应用程序类
     */
    class App : public HttpServer {
    public:
        /**
         * 创建全局对象
         * @param ipaddress 地址
         * @param port 端口
         */
        static void CreateApp(const std::string &ipaddress, unsigned port);
        /**
         * 获取全局对象
         * @return App 全局对象
         */
        static App *GetApp();

        /**
         * 注册一个 Servlet
         * @param servlet_name 服务名称
         * @param url URL
         * @param servlet Servlet 实例
         */
        void regServlet(const string &servlet_name, const string &url, const Servlet::Ptr &servlet);
        /**
         * 启动函数
         */
        void start();
        /**
         * 服务函数
         */
        void exec();
        /**
         * 获取 Servlet 映射表
         * @return Servlet 映射表
         */
        const std::map<string, ServletContext, strcmp<>> &getMap() const;

        void shutdown() override;

    private:
        std::atomic_bool isShutdown = false;
        App(const string &ipaddress, unsigned short port);
        ~App() override;
        static App *app;
        std::map<string, ServletContext, strcmp<>> servletMap;
        ThreadPool pool{8};
    };
}// namespace MyEngine