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
        void regServlet(const string &servlet_name, const string &url, Servlet *servlet);
        /**
         * 启动服务
         * @warning 无限循环
         */
        [[noreturn]] void exec();
        /**
         * 获取 Servlet 映射表
         * @return Servlet 映射表
         */
        const std::map<string, ServletContext, strcmp<>> &getMap() const;

    private:
        App(const string &ipaddress, unsigned short port);
        ~App() override;
        static App *app;
        std::map<string, ServletContext, strcmp<>> servletMap;
    };

    /**
     * @brief Tcp 子线程
     */
    class TcpThread {
    public:
        /**
         * 初始化一个子线程
         * @param client Tcp 连接
         */
        explicit TcpThread(const TcpClient& client);
        /**
         * 子线程主函数
         */
        void Main();

    protected:
        TcpClient client;
    };
}// namespace MyEngine