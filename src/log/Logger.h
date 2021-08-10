/**
 * @file Logger.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 日志输出器
 */
#pragma once
#include <log/LogAppender.h>
#include <vector>

namespace MyEngine{

    /**
     * @brief 日志输出器
     */
    class Logger {
    public:
        /**
         * 智能指针对象
         */
        typedef std::shared_ptr<Logger> Ptr;

        /**
         * 默认构造函数
         */
        Logger() = default;

        /**
         * 添加日志输出地
         * @param appender 日志输出地
         */
        void addAppender(const LogAppender::Ptr& appender);
        /**
         * 输出日志
         * @param event 日志事件
         */
        void log(const LogEvent::Ptr& event);

    private:
        std::vector<LogAppender::Ptr> appenders;
    };

    Logger::Ptr GetGlobalLogger();
}

