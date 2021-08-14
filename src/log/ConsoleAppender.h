/**
 * @file ConsoleAppender.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 控制台输出地
 */
#pragma once
#include <log/LogAppender.h>

namespace MyEngine{

    /**
     * @brief 控制台输出地
     */
    class ConsoleAppender : public LogAppender{
    public:
        ConsoleAppender(LogFormatter::Ptr formatter, LogLevel level);

        void dump(const LogEvent::Ptr &event) override;
    };
}

