/**
 * @file LogFormatter.h
 * @author kaoru
 * @date 2021.8.11
 * @version 0.1
 * @brief 日志信息格式化接口
 */
#pragma once
#include <log/LogEvent.h>

namespace MyEngine {

    /**
     * @brief 日志信息格式化接口
     */
    class LogFormatter {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef std::shared_ptr<LogFormatter> Ptr;

        /**
         * 格式化日志字符串
         * @param event 日志事件
         * @return 字符串
         */
        virtual std::string dump(const LogEvent::Ptr &event) noexcept = 0;
    };
}// namespace MyEngine
