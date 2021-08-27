/**
 * @file ConsoleAppender.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 控制台输出地
 */

#include "ConsoleAppender.h"

#include <utility>
MyEngine::ConsoleAppender::ConsoleAppender(MyEngine::LogFormatter::Ptr formatter, MyEngine::LogLevel level) noexcept
    : LogAppender(std::move(formatter), level) {
}

void MyEngine::ConsoleAppender::dump(const MyEngine::LogEvent::Ptr &event) noexcept {
    setbuf(stdout, nullptr);
    puts(this->formatter->dump(event).c_str());
    fflush(stdout);
}
