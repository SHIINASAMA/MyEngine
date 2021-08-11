/**
 * @file PluginManager.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 
 */
#include "PluginManager.h"

void MyEngine::PluginManager::addPlugin(const MyEngine::Plugin::Ptr &plugin) {
    this->plugins.emplace_back(plugin);
}

void MyEngine::PluginManager::clear() {
    this->plugins.clear();
}

const std::vector<MyEngine::Plugin::Ptr> &MyEngine::PluginManager::getPlugins() const {
    return this->plugins;
}
