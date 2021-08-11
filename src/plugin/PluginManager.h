/**
 * @file PluginManager.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 插件管理器
 */
#pragma once
#include <plugin/Plugin.h>
#include <vector>

namespace MyEngine {

    /**
     * @brief 插件管理器
     */
    class PluginManager {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef std::shared_ptr<PluginManager> Ptr;

        /**
         * 默认构造函数
         */
        PluginManager()          = default;
        /**
         * 默认析构函数
         */
        virtual ~PluginManager() = default;

        /**
         * 添加插件
         * @param plugin 插件
         */
        void addPlugin(const Plugin::Ptr &plugin);
        /**
         * 清除插件
         */
        void clear();

        /**
         * 获取插件集合
         * @return 插件集合
         */
        const std::vector<Plugin::Ptr> &getPlugins() const;

    protected:
        std::vector<Plugin::Ptr> plugins;
    };
}// namespace MyEngine
