/**
 * @file Logger.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 日志输出器实现
 */
#include <log/ConsoleAppender.h>
#include <log/ConsoleFormatter.h>
#include <log/Logger.h>

void MyEngine::Logger::addAppender(const MyEngine::LogAppender::Ptr &appender) {
    this->appenders.emplace_back(appender);
}

void MyEngine::Logger::log(const MyEngine::LogEvent::Ptr &event) {
    for (auto &appender : appenders) {
        appender->dump(event);
    }
}

static MyEngine::Logger::Ptr logger = nullptr;

MyEngine::Logger::Ptr MyEngine::GetGlobalLogger() {
    if (logger == nullptr) {
        logger.reset(new Logger());
        auto formatter = std::make_shared<ConsoleFormatter>();
        auto appender  = std::make_shared<ConsoleAppender>(formatter, LogLevel::DEBUG);
        logger->addAppender(appender);
    }
    return logger;
}
