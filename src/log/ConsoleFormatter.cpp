/**
 * @file ConsoleFormatter.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 控制台日志格式化器
 */
#include <log/ConsoleFormatter.h>
#include <sstream>

std::string MyEngine::ConsoleFormatter::dump(const MyEngine::LogEvent::Ptr &event) noexcept {
    std::stringstream stream;
    time_t time     = event->getTime();
    auto timeStruct = localtime(&time);
    char timeBuffer[64];
    strftime(timeBuffer, 64, "%x %X", timeStruct);
    stream << "[" << GetLevelString(event->getLevel()) << "] "
           << timeBuffer << " "
           << event->getThreadName() << ":" << event->getThreadId() << " "
           << event->getFileName() << ":" << event->getLine() << "> "
           << event->getMessage();
    return stream.str();
}

std::string MyEngine::ConsoleFormatter::GetLevelString(const LogLevel &logLevel) noexcept {
    switch (logLevel) {
        case LogLevel::DEBUG:
            return "\33[1;32mDEBUG\33[0m";
        case LogLevel::INFO:
            return "\33[0;37mINFO \33[0m";
        case LogLevel::WARN:
            return "\33[1;33mWARN \33[0m";
        default:
            return "\33[1;31mERROR\33[0m";
    }
}
