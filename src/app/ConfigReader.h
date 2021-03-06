/**
 * @file ConfigReader.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 配置文件读取器
 */

#pragma once
#include <vector>
#include <yaml-cpp/yaml.h>

namespace MyEngine {

    /**
     * @brief 服务器基础配置
     */
    struct ServerConfig {
        /**
         * @brief 智能指针对象
         */
        typedef std::shared_ptr<ServerConfig> Ptr;

        struct BaseInfo {
            /**
             * 服务器名称
             */
            std::string name;
            /**
             * 运行 IP
             */
            std::string ipaddress;
            /**
             * 运行端口
             */
            unsigned int port;
            /**
             * Web 资源目录
             */
            std::string webDirectory;
            /**
             * 插件目录
             */
            std::string pluginDirectory;
        } baseInfo;

        /**
         * @brief 线程池配置信息
         */
        struct ThreadPoolConfig {
            /**
             * 线程池名称
             */
            std::string name;
            /**
             * 线程数
             */
            size_t threads;
        } threadPoolConfig;

        /**
         * @brief Sqlite log 配置
         */
        struct SqliteLogDb {
            /**
             * 是否启用
             */
            bool enable;
            /**
             * 数据库地址
             */
            std::string location;
        } sqliteLogDb;

        /**
         * @brief log 文件夹配置
         */
        struct FileLogDir{
            /**
             * 是否启用
             */
            bool enable;
            /**
             * 文件夹位置
             */
            std::string location;
        } fileLogDir;
    };

    /**
     * @brief 配置文件读取器
     */
    class ConfigReader {
    public:
        /**
         * 读取服务器配置
         * @param path 配置文件路径
         * @param serverConfig 储存对象
         * @return 是否读取成功
         */
        static bool ReadServerConfig(const std::string &path, const ServerConfig::Ptr &serverConfig);
    };
}// namespace MyEngine
