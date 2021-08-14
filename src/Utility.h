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

/**
 * @brief 快速调用 std::make_shared
 */
#define PTR(TYPE, ...) make_shared<TYPE>(__VA_ARGS__)

/**
 * @brief 调用全局 Logger 输出
 * @warning 请不要不要直接使用该宏
 */
#define LOG(LEVEL, ...)                                                                                                                               \
    {                                                                                                                                                 \
        char buffer[1024];                                                                                                                            \
        sprintf(buffer, __VA_ARGS__);                                                                                                                 \
        time_t tm;                                                                                                                                    \
        time(&tm);                                                                                                                                    \
        auto event = std::make_shared<MyEngine::LogEvent>(tm, LEVEL, MyEngine::GetThreadName(), MyEngine::GetThreadId(), __FILE_NAME__, __LINE__, buffer); \
        MyEngine::GetGlobalLogger()->log(event);                                                                                                      \
    }

/**
 * 输出调试级别日志
 */
#define LOG_DEBUG(...) \
    LOG(MyEngine::LogLevel::DEBUG, __VA_ARGS__)

/**
 * 输出信息级别日志
 */
#define LOG_INFO(...) \
    LOG(MyEngine::LogLevel::INFO, __VA_ARGS__)

/**
 * 输出警告级别日志
 */
#define LOG_WARN(...) \
    LOG(MyEngine::LogLevel::WARN, __VA_ARGS__)

/**
 * 输出错误级别日志
 */
#define LOG_ERROR(...) \
    LOG(MyEngine::LogLevel::ERROR, __VA_ARGS__)
