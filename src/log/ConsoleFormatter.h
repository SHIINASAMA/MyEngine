/**
 * @file ConsoleFormatter.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 控制台日志格式化器
 */
#pragma once
#include <log/LogFormatter.h>

namespace MyEngine{

    /**
     * @brief 控制台日志格式化器
     */
    class ConsoleFormatter : public LogFormatter{
    public:
        std::string dump(LogEvent::Ptr event) override;
    };
}

