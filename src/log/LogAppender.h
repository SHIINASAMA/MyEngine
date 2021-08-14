/**
 * @file LogAppender.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 日志输出地接口
 */
#pragma once
#include <log/LogFormatter.h>

namespace MyEngine {

    /**
     * @brief 日志输出地接口
     */
    class LogAppender {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef std::shared_ptr<LogAppender> Ptr;

        /**
         * 默认构造函数
         */
        LogAppender() = default;
        /**
         * 基础构造函数
         * @param formatter 日志格式化器
         * @param level 日志等级阈值
         */
        LogAppender(LogFormatter::Ptr formatter, LogLevel level);
        /**
         * 输出前处理
         * @param event 日志事件
         */
        void preDump(const LogEvent::Ptr &event);
        /**
         * 输出日志
         * @param event 日志事件
         */
        virtual void dump(const LogEvent::Ptr &event) = 0;
    protected:
        LogFormatter::Ptr formatter;
        LogLevel level;
    };

}// namespace MyEngine
