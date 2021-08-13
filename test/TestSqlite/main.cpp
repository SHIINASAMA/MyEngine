#include <db/sqlite/SqliteHelper.h>

using namespace MyEngine::Sqlite;

const char *sql = "CREATE TABLE \"table\" (\n"
                  "\t\"level\" TEXT CHECK(level IN('DEBUG','INFO','WARN','ERROR')) NOT NULL,\n"
                  "\t\"time\" DATETIME NOT NULL,\n"
                  "\t\"threadName\" TEXT NOT NULL,\n"
                  "\t\"threadId\" TINYINT NOT NULL,\n"
                  "\t\"fileName\" TEXT NOT NULL,\n"
                  "\t\"fileLine\" TINYINT NOT NULL,\n"
                  "\t\"message\" TEXT NOT NULL\n"
                  ")\n"
                  ";";

int main() {
    SqliteHelper helper;
    helper.open("test.db");
    if (!helper.exec(sql)) {
        helper.close();
        return -1;
    }
    helper.close();
    return 0;
}