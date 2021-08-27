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

    /**
     * @brief Sqlite 日志输出地
     */
    class SqliteAppender : public LogAppender{
    public:
        /**
         * 智能指针对象
         */
        typedef shared_ptr<SqliteAppender> Ptr;

        /**
         * 默认构造函数
         * @param path 数据库路径，不存在则自动创建
         * @param level 日志等级阈值
         */
        SqliteAppender(const string &path, LogLevel level) noexcept;
        /**
         * 默认析构函数
         */
        virtual ~SqliteAppender() noexcept = default;

        /**
         * 写入日志
         * @param event 日志事件
         */
        void dump(const LogEvent::Ptr& event) noexcept override;

        /**
         * 获取等级字符串
         * @param level 日志等级
         * @return 等级字符串
         */
        static string GetLevelString(LogLevel level) noexcept;
        /**
         * 格式化时间未 Sqlite 模式
         * @param time 时间
         * @return 指定格式
         */
        static string timeFormat(time_t time) noexcept;
    private:

        bool log = true;
        string dbPath;
        string tableName;
        Sqlite::SqliteHelper::Ptr sqlite;
    };
}

