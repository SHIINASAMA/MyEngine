/**
* @file FileAppender.h
* @author kaoru
* @date 2021/11/18
* @version 0.1
* @brief 文件输出地实现
*/

#include <log/FileAppender.h>
#include <sstream>
#include <Utility.h>

namespace MyEngine {

    FileAppender::FileAppender(const std::string &logDir, LogLevel level) noexcept {
        this->level = level;

        time_t tm;
        time(&tm);
        auto timeStruct = localtime(&tm);
        char timeBuffer[64];
        strftime(timeBuffer, 64, "%Y-%m-%d %X", timeStruct);

        std::stringstream temp;
        temp << "./" << logDir << "/" << timeBuffer << ".log";
        this->currentFile = temp.str();
        stream.open(this->currentFile);
    }

    FileAppender::~FileAppender() noexcept {
        if (stream.is_open()){
            stream.close();
        }
    }

    void FileAppender::dump(const LogEvent::Ptr &event) noexcept {
        if(stream.is_open()) {
            time_t time     = event->getTime();
            auto timeStruct = localtime(&time);
            char timeBuffer[64];
            strftime(timeBuffer, 64, "%x %X", timeStruct);
            stream << "[" << GetLevelString(event->getLevel()) << "] "
                   << timeBuffer << " "
                   << event->getThreadName() << ":" << event->getThreadId() << " "
                   << event->getFileName() << ":" << event->getLine() << "> "
                   << event->getMessage() << "\n";
            stream.flush();
        } else {
            printf("文件打开错误 %s\n", strerror(errno));
        }
    }

    std::string FileAppender::GetLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO ";
            case LogLevel::WARN:
                return "WARN ";
            default:
                return "ERROR";
        }
    }

}
