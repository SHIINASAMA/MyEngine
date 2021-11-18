/**
* @file FileAppender.h
* @author kaoru
* @date 2021/11/18
* @version 0.1
* @brief 文件输出地
*/
#pragma once
#include <fstream>
#include <log/LogAppender.h>

namespace MyEngine {

    /**
     * @brief 文件日志输出地
     */
    class FileAppender : public LogAppender {
    public:

        typedef std::shared_ptr<FileAppender> Ptr;

        FileAppender(const std::string &logDir, LogLevel level) noexcept;
        ~FileAppender() noexcept;

        void dump(const LogEvent::Ptr &event) noexcept override;

        std::string getCurrentFileName() const { return this->currentFile; }

    private:

        static std::string GetLevelString(LogLevel level);

        std::ofstream stream;
        std::string currentFile;
    };

}