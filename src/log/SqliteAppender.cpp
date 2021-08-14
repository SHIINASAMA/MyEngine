/**
 * @file SqliteAppender.cpp
 * @author kaoru
 * @date 2021/8/14
 * @version 0.1
 * @brief Sqlite 日志输出地实现
 */
#include <log/SqliteAppender.h>
#include <sstream>

MyEngine::SqliteAppender::SqliteAppender(const string &path, LogLevel level) : LogAppender(nullptr, level), dbPath(path) {
    this->sqlite = make_shared<Sqlite::SqliteHelper>();
    if (!sqlite->open(path)) {
        LOG_WARN("日志数据库打开失败，停止记录日志");
        this->log = false;
        return;
    }

    time_t t;
    time(&t);
    this->tableName = timeFormat(t);

    string sql = "CREATE TABLE \"" + this->tableName + "\" (\n"
                                                       "\t\"level\" TEXT NOT NULL,\n"
                                                       "\t\"time\" DATETIME NOT NULL,\n"
                                                       "\t\"threadName\" TEXT NOT NULL,\n"
                                                       "\t\"threadId\" TINYINT NOT NULL,\n"
                                                       "\t\"fileName\" TEXT NOT NULL,\n"
                                                       "\t\"fileLine\" TINYINT NOT NULL,\n"
                                                       "\t\"message\" TEXT NOT NULL\n"
                                                       ")\n"
                                                       ";";
    if (!sqlite->exec(sql)) {
        LOG_WARN("日志数据库建表失败，停止记录日志");
        this->log = false;
    }
}

string MyEngine::SqliteAppender::timeFormat(time_t time) {
    auto tm = localtime(&time);
    char buffer[64];
    strftime(buffer, 64, "%Y-%m-%d %X", tm);
    return {buffer};
}

void MyEngine::SqliteAppender::dump(const MyEngine::LogEvent::Ptr& event) {
    if (this->log) {
        std::stringstream stream;
        stream << "INSERT INTO \"" << tableName << "\" (level,time,threadName,threadId,fileName,fileLine,message)\n"
               << "VALUES (\'" << GetLevelString(event->getLevel())
               << "\',\'" << timeFormat(event->getTime())
               << "\',\'" << event->getThreadName()
               << "\'," << event->getThreadId()
               << ",\'" << event->getFileName()
               << "\'," << event->getLine()
               << ",\'" << event->getMessage()
               << "\');";
        sqlite->exec(stream.str());
    }
}

string MyEngine::SqliteAppender::GetLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        default:
            return "ERROR";
    }
}
