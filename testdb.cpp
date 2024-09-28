#include <iostream>
#include <sqlite3.h>

void checkDatabase(const char* dbFile) {
    sqlite3* db;
    char* errorMsg = nullptr;
    int rc;

    // Открыть базу данных
    rc = sqlite3_open(dbFile, &db);
    if (rc) {
        std::cerr << "Не удалось открыть базу данных: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Проверить количество таблиц в базе данных
    const char* countTablesQuery = "SELECT count(*) FROM sqlite_master WHERE type='table';";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, countTablesQuery, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int tableCount = sqlite3_column_int(stmt, 0);
        std::cout << "Количество таблиц: " << tableCount << std::endl;
    }
    sqlite3_finalize(stmt);

    // Получить информацию о таблицах и их максимальной нагрузке (количество записей)
    const char* tableInfoQuery = "SELECT name FROM sqlite_master WHERE type='table';";
    rc = sqlite3_prepare_v2(db, tableInfoQuery, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* tableName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string countRowsQuery = "SELECT count(*) FROM " + std::string(tableName) + ";";
        sqlite3_stmt* countStmt;
        rc = sqlite3_prepare_v2(db, countRowsQuery.c_str(), -1, &countStmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Ошибка выполнения запроса для таблицы " << tableName << ": " << sqlite3_errmsg(db) << std::endl;
            continue;
        }

        if (sqlite3_step(countStmt) == SQLITE_ROW) {
            int rowCount = sqlite3_column_int(countStmt, 0);
            std::cout << "Таблица: " << tableName << ", количество записей: " << rowCount << std::endl;
        }
        sqlite3_finalize(countStmt);

        // Получить информацию о типах столбцов
        std::string pragmaQuery = "PRAGMA table_info(" + std::string(tableName) + ");";
        sqlite3_stmt* columnStmt;
        rc = sqlite3_prepare_v2(db, pragmaQuery.c_str(), -1, &columnStmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Ошибка выполнения запроса для таблицы " << tableName << ": " << sqlite3_errmsg(db) << std::endl;
            continue;
        }

        std::cout << "Столбцы и их типы для таблицы " << tableName << ":" << std::endl;
        while (sqlite3_step(columnStmt) == SQLITE_ROW) {
            const char* columnName = reinterpret_cast<const char*>(sqlite3_column_text(columnStmt, 1));
            const char* columnType = reinterpret_cast<const char*>(sqlite3_column_text(columnStmt, 2));
            std::cout << "  Столбец: " << columnName << ", Тип: " << columnType << std::endl;
        }
        sqlite3_finalize(columnStmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char* dbFile = "db/output.db";
    checkDatabase(dbFile);
    return 0;
}