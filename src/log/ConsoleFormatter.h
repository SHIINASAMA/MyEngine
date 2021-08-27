/**
 * @file ConsoleFormatter.h
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 控制台日志格式化器
 */
#pragma once
#include <log/LogFormatter.h>

namespace MyEngine {

    /**
     * @brief 控制台日志格式化器
     */
    class ConsoleFormatter : public LogFormatter {
    public:
        std::string dump(const LogEvent::Ptr &event) noexcept override;

        /**
          * 获取带色彩的日志等级字符串
          * @param level 日志等级
          * @return 字符串
          */
        static std::string GetLevelString(const LogLevel &level) noexcept;
    };
}// namespace MyEngine
