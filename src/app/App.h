/**
 * @file App.h
 * @author kaoru
 * @date 2021.8.8
 * @brief 应用程序类
 * @version 0.1
 */
#pragma once
#include <app/ConfigReader.h>
#include <atomic>
#include <http/HttpServer.h>
#include <plugin/Plugin.h>
#include <servlet/ServletContext.h>
#include <thread/ThreadPool.h>

namespace MyEngine {

    /**
     * @brief 应用程序类
     */
    class App : public HttpServer {
    public:
        typedef shared_ptr<App> Ptr;
        /**
         * 创建全局对象
         * @param config 配置文件
         */
        static void CreateApp(const ServerConfig::Ptr &config);
        /**
         * 获取全局对象
         * @return App 全局对象
         */
        static App::Ptr GetApp();
        /**
         * 默认析构函数
         */
        ~App() override;

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
         * 根据 url 获取对应的 ServletContext
         * @param url 目标 url
         * @return 不存在则会返回 nullptr
         */
        ServletContext::Ptr findServletContextByUrl(const string &url);

        /**
         * 关闭服务
         */
        void shutdown() override;
        /**
         * 获取插件中间目录名
         * @return 插件中间目录名
         */
        string getPluginDir() const { return this->serverConfig->pluginDirectory; };
        /**
         * 获取 Web 资源中间目录名
         * @return Web 资源中间目录名
         */
        string getWebDir() const { return this->serverConfig->webDirectory; }
        /**
         * 获取服务器名称
         * @return 服务器名称
         */
        string getServerName() const { return this->serverConfig->name; }

        /**
         * 重新加载插件
         * @warning 这可能会导致其他用户 Servlet 在插件重载完成前无法使用
         */
        void reload();

    private:
        void exec();
        explicit App(const ServerConfig::Ptr &config);

        pthread_rwlock_t lock{};
        std::atomic_bool isShutdown = false;
        static App::Ptr app;
        std::map<string, ServletContext::Ptr, strcmp<>> servletMap;
        std::vector<Plugin::Ptr> plugins;
        ThreadPool::Ptr pool;
        ServerConfig::Ptr serverConfig;
        std::shared_ptr<std::thread> background;
    };
}// namespace MyEngine