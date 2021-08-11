#include <Utility.h>
#include <cstring>
#include <plugin/Plugin.h>

using namespace MyEngine;

int main() {
    auto p = std::make_shared<Plugin>("./libPlugin.so");
    if (!p->open()) {
        puts(dlerror());
        return -1;
    }

    auto manifest = p->getManifest();
    LOG_INFO("Plugin name: %s", manifest->name);
    LOG_INFO("Plugin Version: %d", manifest->version);
    LOG_INFO("Plugin author: %s", manifest->author);
    LOG_INFO("Plugin build date: %ld", manifest->time);
    LOG_INFO("Plugin entry: %p", manifest->entry);

    return 0;
}