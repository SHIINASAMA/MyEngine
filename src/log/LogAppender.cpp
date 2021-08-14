/**
 * @file LogAppender.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 日志输出地接口
 */
#include <log/LogAppender.h>

MyEngine::LogAppender::LogAppender(LogFormatter::Ptr formatter, LogLevel level)
    : formatter(std::move(formatter)),
      level(level) {
}

void MyEngine::LogAppender::preDump(const LogEvent::Ptr &event) {
    if (event->getLevel() >= level) {
        dump(event);
    }
}
