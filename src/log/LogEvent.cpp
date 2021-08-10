/**
 * @file LogEvent.cpp
 * @author kaoru
 * @date 2021.8.11
 * @version 0.1
 * @brief 日志事件
 */
#include <log/LogEvent.h>

#include <utility>

std::string MyEngine::GetLevelString(const LogLevel &logLevel) {
    switch (logLevel) {
        case LogLevel::DEBUG:
            return "\33[1;32mDEBUG\33[0m";
        case LogLevel::INFO:
            return "\33[0;37mINFO \33[0m";
        case LogLevel::WARN:
            return "\33[1;33mWARN \33[0m";
        case LogLevel::ERROR:
            return "\33[1;31mERROR\33[0m";
        default:
            return "ERROR";
    }
}

MyEngine::LogEvent::LogEvent(time_t tm, MyEngine::LogLevel lv, std::string name, pid_t id, const char *file, int32_t line, std::string m)
    : time(tm),
      level(lv),
      threadName(std::move(name)),
      threadId(id),
      file(file),
      line(line),
      message(std::move(m)) {
}
