/**
 * @file Plugin.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 插件类
 */
#pragma once
#include <dlfcn.h>
#include <memory>
#include <servlet/HttpServlet.h>

namespace MyEngine {

    /**
     * @brief 插件清单
     */
    struct Manifest{
        typedef void *(*PluginEntry)();

        /**
         * @brief 插件名称
         */
        const char *name;
        /**
         * @brief 插件版本
         */
        int version;
        /**
         * @brief 插件作者
         */
        const char *author;
        /**
         * @brief Servlet Url
         */
        const char *url;
        /**
         * @brief 时间戳
         */
        time_t time;
        /**
         * @brief 资源创建入口
         */
        PluginEntry entry;
    };

    /**
     * @brief 插件类
     */
    class Plugin {
    public:
        /**
         * 智能指针对象
         */
        typedef std::shared_ptr<Plugin> Ptr;

        /**
         * 从文件中加载插件
         * @param path 路径
         */
        explicit Plugin(const std::string &path);
        /**
         * 默认析构函数
         */
        virtual ~Plugin();

        /**
         * 打开当前指定路径的文件
         * @return 是否成功
         */
        bool open();
        /**
         * 获取清单文件
         * @return 清单文件
         */
        Manifest *getManifest();

        /**
         * 获取插件路径
         * @return 插件路径
         */
        std::string getPath() const { return this->path; }

    protected:
        void *handle = nullptr;
        std::string path;
    };
}// namespace MyEngine
