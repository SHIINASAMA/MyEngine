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
        YAML::Node config = YAML::LoadFile(path);

        serverConfig->baseInfo.name            = config["base-info"]["name"].as<std::string>();
        serverConfig->baseInfo.ipaddress       = config["base-info"]["ip-address"].as<std::string>();
        serverConfig->baseInfo.port            = config["base-info"]["port"].as<unsigned short>();
        serverConfig->baseInfo.webDirectory    = config["base-info"]["web-directory"].as<std::string>();
        serverConfig->baseInfo.pluginDirectory = config["base-info"]["plugin-directory"].as<std::string>();

        serverConfig->threadPoolConfig.name    = config["thread-pool"]["name"].as<std::string>();
        serverConfig->threadPoolConfig.threads = config["thread-pool"]["threads"].as<size_t>();

        serverConfig->sqliteLogDb.enable   = config["sqlite-log-db"]["enable"].as<bool>();
        serverConfig->sqliteLogDb.location = config["sqlite-log-db"]["location"].as<std::string>();

        return true;
    } catch (YAML::Exception &exception) {
        LOG_DEBUG("%s", exception.what());
        return false;
    }
}
