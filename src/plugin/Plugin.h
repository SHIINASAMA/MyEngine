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

    struct Manifest{
        typedef void *(*PluginEntry)();

        const char *name;
        int version;
        const char *author;
        time_t time;
        PluginEntry entry;
    };

    /**
     * 插件类
     */
    class Plugin {
    public:
        typedef std::shared_ptr<Plugin> Ptr;

        explicit Plugin(const std::string &path);
        virtual ~Plugin();

        bool open();
        Manifest *getManifest();

        std::string getPath() const { return this->path; }

    protected:
        void *handle = nullptr;
        std::string path;
    };
}// namespace MyEngine
