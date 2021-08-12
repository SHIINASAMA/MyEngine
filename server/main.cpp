#include <app/App.h>
#include <csignal>
#include <iostream>

bool isLoop = false;
void call(int code) {
    if (code == SIGINT) {
        if (isLoop) {
            MyEngine::App::GetApp()->shutdown();
        }
        exit(0);
    }
}

int main(int argc, char **argv) {
    signal(SIGINT, call);

    if (argc != 2) {
        LOG_ERROR("A file path parameter is required\n");
        return -1;
    }

    auto config = std::make_shared<MyEngine::ServerConfig>();
    if (!MyEngine::ConfigReader::ReadServerConfig(argv[1], config)) {
        LOG_ERROR("File opening failure\n");
        return -1;
    }

    MyEngine::App::CreateApp(config);
    auto app = MyEngine::App::GetApp();
    app->start();
    isLoop = true;
    string cmd;
    while (true) {
        std::cin >> cmd;
        if (cmd == "exit" || cmd == "q") {
            //todo: Can't stop correctly in wsl
            app->shutdown();
            break;
        } else if (cmd == "reload") {
            app->reload();
        } else if (cmd == "info") {
            LOG_INFO("Server name: %s", config->name.c_str());
            LOG_INFO("Listening:   %s:%d", config->ipaddress.c_str(), config->port);
            LOG_INFO("Web Dir:     %s", config->webDirectory.c_str());
            LOG_INFO("Plugins Dir: %s", config->pluginDirectory.c_str());
            LOG_INFO("Thread Pool: %s:%zu", config->threadPoolConfig.name.c_str(), config->threadPoolConfig.threads);
        } else {
            LOG_WARN("Unknown commend");
        }
    }
    return 0;
}