/**
 * @file SqliteHelper.h
 * @author kaoru
 * @date 2021/8/13
 * @version 0.1
 * @brief Sqlite 基础功能简单封装
 */
#pragma once
#include <Utility.h>
#include <sqlite3.h>
#include <mutex>

/**
 * @anchor MAKE_ROW_AND_COLUMN
 * @brief 生成一对行号与列号的
 * @param r 行号
 * @param c 列号
 */
#define MAKE_ROW_AND_COLUMN(r, c) std::make_pair<int, int>(r, c)

namespace MyEngine::Sqlite {

    /**
     * @brief Sqlite 查询结果
     */
    class SqliteResult {
    public:
        /**
         * 智能指针对象
         */
        typedef shared_ptr<SqliteResult> Ptr;

        /**
         * 构造函数
         * @param rawPtr 原始字符串指针
         * @param rows 行数
         * @param columns 列数
         */
        explicit SqliteResult(char **rawPtr, int rows, int columns);
        /**
         * 析构函数
         */
        virtual ~SqliteResult();

        /**
         * 获取表格
         * @return 二维字符串数组
         */
        char **getTable();
        /**
         * 获取具体的一项数据
         * @param row 行号
         * @param column 列号
         * @return 数据字符串
         */
        char *getItem(int row, int column);

        /**
         * 获取表格的行数
         * @return 表格的行数
         */
        int getRows() const { return this->rows; }
        /**
         * 获取表格的列数
         * @return 表格的列数
         */
        int getColumns() const { return this->columns; }

        /**
         * @brief 获取具体的一项数据，可以使用 @ref MAKE_ROW_AND_COLUMN 快速生成
         * @param rowAndColumns 行号与列号
         * @return 数据字符串
         */
        const char* operator[](std::pair<int, int> rowAndColumns) const;

    private:
        int rows;
        int columns;
        char **raw = nullptr;
    };

    /**
     * @brief Sqlite 帮助类
     */
    class SqliteHelper {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef shared_ptr<SqliteHelper> Ptr;

        /**
         * 默认构造函数
         */
        SqliteHelper() = default;
        /**
         * 析构函数
         */
        virtual ~SqliteHelper();

        /**
         * 打开数据库
         * @param path 数据库文件路径，不存在则会创建
         * @return 是否打开成功
         */
        bool open(const string &path);
        /**
         * 执行 select 语句，有返回值的查询语句
         * @param sql sql 语句
         * @param result 查询结果
         * @return 是否执行成功
         */
        bool select(const string &sql, SqliteResult::Ptr &result);
        /**
         * 执行没有返回值的 sql 语句
         * @param sql 查询结果
         * @return 是否执行成功
         */
        bool exec(const string &sql);
        /**
         * 关闭当前数据库连接
         * @return 是否成功
         */
        bool close();

    protected:
        std::mutex mutex;
        sqlite3 *raw = nullptr;
    };
}// namespace MyEngine::Sqlite
