/**
 * @file SqliteAppender.h
 * @author kaoru
 * @date 2021/8/14
 * @version 0.1
 * @brief Sqlite 日志输出地
 */
#pragma once
#include <log/LogAppender.h>
#include <db/sqlite/SqliteHelper.h>

namespace MyEngine{

    class SqliteAppender : public LogAppender{
    public:
        typedef shared_ptr<SqliteAppender> Ptr;

        SqliteAppender(const string &path, LogLevel level);
        virtual ~SqliteAppender() = default;

        void dump(const LogEvent::Ptr& event) override;

        static string GetLevelString(LogLevel level);
        static string timeFormat(time_t time);
    private:

        bool log = true;
        string dbPath;
        string tableName;
        Sqlite::SqliteHelper::Ptr sqlite;
    };
}

