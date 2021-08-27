/**
 * @file SqliteHelper.cpp
 * @author kaoru
 * @date 2021/8/13
 * @version 0.1
 * @brief Sqlite 基础功能简单封装的实现
 */
#include "SqliteHelper.h"

MyEngine::Sqlite::SqliteResult::SqliteResult(char **rawPtr, int rows, int columns) noexcept {
    this->raw     = rawPtr;
    this->rows    = rows;
    this->columns = columns;
}

MyEngine::Sqlite::SqliteHelper::~SqliteHelper() noexcept {
    this->close();
}

MyEngine::Sqlite::SqliteResult::~SqliteResult() noexcept {
    sqlite3_free_table(this->raw);
}

char **MyEngine::Sqlite::SqliteResult::getTable() noexcept {
    return raw;
}

char *MyEngine::Sqlite::SqliteResult::getItem(int row, int column) noexcept {
    return raw[(rows + 1) * row + column];
}

const char *MyEngine::Sqlite::SqliteResult::operator[](std::pair<int, int> rowAndColumns) const noexcept {
    return raw[(rows + 1) * rowAndColumns.first + rowAndColumns.second];
}

bool MyEngine::Sqlite::SqliteHelper::open(const string &path) noexcept {
    return sqlite3_open_v2(path.c_str(), &this->raw, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL) == SQLITE_OK;
}

bool MyEngine::Sqlite::SqliteHelper::close() noexcept {
    if (raw) {
        auto rt = sqlite3_close_v2(raw) == SQLITE_OK;
        if (rt) {
            raw = nullptr;
            return true;
        }
        return false;
    }
    return true;
}

bool MyEngine::Sqlite::SqliteHelper::exec(const string &sql) noexcept {
    int rows;
    int columns;
    char *error;
    char **table;
    std::unique_lock<std::mutex> lock(this->mutex);
    if (sqlite3_get_table(this->raw, sql.c_str(), &table, &rows, &columns, &error) == SQLITE_OK) {
        return true;
    }
    return false;
}

bool MyEngine::Sqlite::SqliteHelper::select(const string &sql, SqliteResult::Ptr &result) noexcept {
    int rows;
    int columns;
    char *error;
    char **table;
    std::unique_lock<std::mutex>lock(this->mutex);
    if (sqlite3_get_table(this->raw, sql.c_str(), &table, &rows, &columns, &error) == SQLITE_OK) {
        result.reset(new SqliteResult(table, rows, columns));
        return true;
    }
    return false;
}