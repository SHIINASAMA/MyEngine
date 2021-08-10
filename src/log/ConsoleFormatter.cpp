/**
 * @file ConsoleFormatter.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 控制台日志格式化器
 */
#include <log/ConsoleFormatter.h>
#include <sstream>

std::string MyEngine::ConsoleFormatter::dump(MyEngine::LogEvent::Ptr event) {
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
