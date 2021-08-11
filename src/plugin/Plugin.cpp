/**
 * @file Plugin.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 插件类定义
 */
#include <plugin/Plugin.h>

MyEngine::Plugin::Plugin(const std::string &path) {
    this->path = path;
}

bool MyEngine::Plugin::open() {
    this->handle = dlopen(path.c_str(), RTLD_LAZY);
    return this->handle != nullptr;
}

MyEngine::Manifest *MyEngine::Plugin::getManifest() {
    return (MyEngine::Manifest *)dlsym(this->handle, "manifest");
}

MyEngine::Plugin::~Plugin() {
    if (this->handle) {
        dlclose(this->handle);
    }
}
