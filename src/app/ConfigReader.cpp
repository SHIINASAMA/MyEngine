/**
 * @file ConfigReader.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 配置文件读取器实现
 */

#include <Utility.h>
#include <app/ConfigReader.h>

bool MyEngine::ConfigReader::ReadServerConfig(const std::string &path, const MyEngine::ServerConfig::Ptr &serverConfig) {
    try {
        YAML::Node config = YAML::LoadFile(path)["server"];

        serverConfig->name            = config["name"].as<std::string>();
        serverConfig->ipaddress       = config["ip-address"].as<std::string>();
        serverConfig->port            = config["port"].as<unsigned short>();
        serverConfig->webDirectory    = config["web-directory"].as<std::string>();
        serverConfig->pluginDirectory = config["plugin-directory"].as<std::string>();

        serverConfig->threadPoolConfig.name    = config["thread-pool"]["name"].as<std::string>();
        serverConfig->threadPoolConfig.threads = config["thread-pool"]["threads"].as<size_t>();

        return true;
    } catch (YAML::Exception &exception) {
        LOG_DEBUG("%s", exception.what());
        return false;
    }
}
