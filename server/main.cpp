#include <app/App.h>
#include <iostream>
#include <log/SqliteAppender.h>
#include <log/FileAppender.h>
#include <CArgs.h>

void help(char **argv);
void start(const char *config_path);

int main(int argc, char **argv) {
//    if (argc != 2) {
//        LOG_ERROR("A file path parameter is required\n");
//        return -1;
//    }

    CARGS_SET_NO_MATCH_CALLBACK_FUNC(help);
    CARGS_NOT_ESSENTIAL("-conf-path", "config.yaml");
    CARGS_INIT(argc, argv);
    const char *value = nullptr;
    if(CARGS_GET_VALUE_BY_KEY("-conf-path", &value)){
        start(value);
    }
    return 0;
}

void help(char **argv){
    puts("感谢您使用 MyEngine Server");
    puts("使用方法：Server --config-path /path/to/config");
}

void start(const char *config_path){
    auto config = std::make_shared<MyEngine::ServerConfig>();
    if (!MyEngine::ConfigReader::ReadServerConfig(config_path, config)) {
        LOG_ERROR("File opening failure\n");
        return;
    }

    if (config->sqliteLogDb.enable) {
        LOG_INFO("加载日志数据库");
        auto sqliteAppender = std::make_shared<MyEngine::SqliteAppender>(config->sqliteLogDb.location, MyEngine::LogLevel::DEBUG);
        MyEngine::GetGlobalLogger()->addAppender(sqliteAppender);
    }

    if (config->fileLogDir.enable) {
        //todo: log to file
        auto fileAppender = std::make_shared<MyEngine::FileAppender>(config->fileLogDir.location, MyEngine::LogLevel::DEBUG);
        MyEngine::GetGlobalLogger()->addAppender(fileAppender);
        LOG_INFO("加载日志文件记录 - %s", fileAppender->getCurrentFileName().c_str());
    }

    MyEngine::App::CreateApp(config);
    auto app = MyEngine::App::GetApp();
    app->start();
    string cmd;
    while (true) {
        std::cin >> cmd;
        if (cmd == "exit" || cmd == "q") {
            //todo: Can't stop correctly in wsl
            LOG_INFO("Try to exit");
            app->shutdown();
            LOG_INFO("Success");
            break;
        } else if (cmd == "reload") {
            LOG_INFO("开始重载插件");
            app->reload();
            LOG_INFO("插件重载完成")
        } else if (cmd == "info") {
            LOG_INFO("Server name:  %s", config->baseInfo.name.c_str());
            LOG_INFO("Listening:    %s:%d", config->baseInfo.ipaddress.c_str(), config->baseInfo.port);
            LOG_INFO("Web Dir:      %s", config->baseInfo.webDirectory.c_str());
            LOG_INFO("Plugins Dir:  %s", config->baseInfo.pluginDirectory.c_str());
            LOG_INFO("Sqlite Log DB:%d:%s", config->sqliteLogDb.enable, config->sqliteLogDb.location.c_str());
            LOG_INFO("Thread Pool:  %s:%zu", config->threadPoolConfig.name.c_str(), config->threadPoolConfig.threads);
        } else {
            LOG_WARN("Unknown commend");
        }
    }
}