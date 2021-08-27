/**
 * @file LogEvent.cpp
 * @author kaoru
 * @date 2021.8.11
 * @version 0.1
 * @brief 日志事件
 */
#include <log/LogEvent.h>

#include <utility>

MyEngine::LogEvent::LogEvent(time_t tm, MyEngine::LogLevel lv, std::string name, pid_t id, const char *file, int32_t line, std::string m) noexcept
    : time(tm),
      level(lv),
      threadName(std::move(name)),
      threadId(id),
      file(file),
      line(line),
      message(std::move(m)) {
}
