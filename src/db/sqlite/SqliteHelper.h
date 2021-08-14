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

#define MAKE_ROW_AND_COLUMN(r, c) std::make_pair<int, int>(r, c)

namespace MyEngine::Sqlite {

    class SqliteResult {
    public:
        typedef shared_ptr<SqliteResult> Ptr;

        explicit SqliteResult(char **rawPtr, int rows, int columns);
        virtual ~SqliteResult();

        char **getTable();
        char *getItem(int row, int column);

        int getRows() const { return this->rows; }
        int getColumns() const { return this->columns; }

        const char* operator[](std::pair<int, int> rowAndColumns) const;

    private:
        int rows;
        int columns;
        char **raw = nullptr;
    };

    class SqliteHelper {
    public:
        typedef shared_ptr<SqliteHelper> Ptr;

        SqliteHelper() = default;
        virtual ~SqliteHelper();

        bool open(const string &path);
        bool select(const string &sql, SqliteResult::Ptr &result);
        bool exec(const string &sql);

        bool close();

    protected:
        std::mutex mutex;
        sqlite3 *raw = nullptr;
    };
}// namespace MyEngine::Sqlite
