/**
 * @file LogEvent.h
 * @author kaoru
 * @date 2021.8.11
 * @version 0.1
 * @brief 日志事件
 */

#pragma once
#include <memory>

namespace MyEngine {

    /**
     * \brief 日志事件等级
     */
    enum class LogLevel {
        /**
         * \brief 调试
         */
        DEBUG = 0,
        /**
         * \brief 信息
         */
        INFO  = 1,
        /**
         * \brief 警告
         */
        WARN  = 2,
        /**
         * \brief 错误
         */
        ERROR = 3,
    };

    /**
     * @brief 日志事件类
     */
    class LogEvent {
    public:
        /**
         * @brief 对象智能指针
         */
        typedef std::shared_ptr<LogEvent> Ptr;

    public:
        /**
         * 默认构造函数
         * @param tm 时间
         * @param lv 等级
         * @param name 线程名称
         * @param id 线程ID
         * @param file 文件
         * @param line 行号
         * @param m 信息
         */
        LogEvent(time_t tm, LogLevel lv, std::string thread, pid_t id, const char *file, int32_t line, std::string m) noexcept;

        /**
         * 获取时间
         * @return 时间
         */
        time_t getTime() const noexcept { return this->time; }
        /**
         * 获取事件等级
         * @return 事件等级
         */
        LogLevel getLevel() const noexcept { return this->level; }
        /**
         * 获取线程 ID
         * @return 线程 ID
         */
        pid_t getThreadId() const noexcept { return this->threadId; }
        /**
         * 获取文件名称
         * @return 文件名称
         */
        const char *getFileName() const noexcept { return this->file; }
        /**
         * 获取行号
         * @return 行号
         */
        int32_t getLine() const noexcept { return this->line; }
        /**
         * 获取信息
         * @return 信息
         */
        std::string getMessage() const noexcept { return this->message; }
        /**
         * 获取线程名称
         * @return 线程名称
         */
        std::string getThreadName() const noexcept {return this->threadName;}

    private:
        time_t time;
        LogLevel level;
        std::string threadName;
        pid_t threadId;
        const char *file = nullptr;
        int32_t line;
        std::string message;
    };
}// namespace MyEngine
