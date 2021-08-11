/**
 * @file main.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 插件清单查看器
 */
#include <cstdio>
#include <plugin/Plugin.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        puts("A file path parameter is required\n");
        return -1;
    }

    auto plugin = std::make_shared<MyEngine::Plugin>(argv[1]);
    if (!plugin->open()) {
        puts("File opening failure\n");
        return -1;
    }

    auto manifest = plugin->getManifest();
    if (!manifest) {
        puts("Failed to obtain the manifest file\n");
        return -1;
    }

    auto tm = localtime(&manifest->time);
    char buffer[64];
    strftime(buffer, 64, "%c", tm);

    printf("name:    %s\n", manifest->name);
    printf("version: %d\n", manifest->version);
    printf("author:  %s\n", manifest->author);
    printf("date:    %ld -> %s\n", manifest->time, buffer);
    printf("entry:   %p\n", manifest->entry);

    return 0;
}