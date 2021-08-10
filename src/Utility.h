/**
 * @file Utility.h
 * @author kaoru
 * @date 2021.8.9
 * @brief 工具头文件
 */

#pragma once
#include <cstring>
#include <log/Logger.h>
#include <memory>
#include <string>
#include <thread/ThreadPool.h>

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::stringstream;

#define PTR(TYPE, ...) make_shared<TYPE>(__VA_ARGS__)

#define LOG(LEVEL, ...)                                                                                                                               \
    {                                                                                                                                                 \
        char buffer[1024];                                                                                                                            \
        sprintf(buffer, __VA_ARGS__);                                                                                                                 \
        time_t tm;                                                                                                                                    \
        time(&tm);                                                                                                                                    \
        auto event = std::make_shared<MyEngine::LogEvent>(tm, LEVEL, MyEngine::GetThreadName(), MyEngine::GetThreadId(), __FILE_NAME__, __LINE__, buffer); \
        MyEngine::GetGlobalLogger()->log(event);                                                                                                      \
    }

#define LOG_DEBUG(...) \
    LOG(MyEngine::LogLevel::DEBUG, __VA_ARGS__)

#define LOG_INFO(...) \
    LOG(MyEngine::LogLevel::INFO, __VA_ARGS__)

#define LOG_WARN(...) \
    LOG(MyEngine::LogLevel::WARN, __VA_ARGS__)

#define LOG_ERROR(...) \
    LOG(MyEngine::LogLevel::ERROR, __VA_ARGS__)
