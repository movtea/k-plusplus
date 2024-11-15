/**
 * @file outputDB.h
 * @brief Модуль, необходимый для создания и заполнения пораждаемых бах данных
 */
#ifndef OUTPUT_DB_H
#define OUTPUT_DB_H

#include "../../lib/sqlite3/sqlite3.h"
#include "../../models/fileSchema.h"
#include <iostream>
#include <filesystem>

using namespace std;

/**
 * Класс для работы с пораждаемыми базами данных
 */
class OutputDB
{
private:
    sqlite3 *DB;
    class OutputDBException // Для проброса ошибок открытия БД
    {
    public:
        int error;
        string messages;
        OutputDBException(string Messages, int Error) { error = Error; messages = Messages;};
    };

public:
    OutputDB(filesystem::path path)
    {
        int err = sqlite3_open(path.string().c_str(), &DB);
        if (err != SQLITE_OK)
        {
            throw OutputDBException("Output db Open error: ", err);
        }
        string create_known_table = "CREATE TABLE IF NOT EXISTS KNOWN_FILES ("
                                    "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "NAME TEXT,"
                                    "PATH TEXT,"
                                    "HASH TEXT"
                                    ");";
        string create_unknown_table = "CREATE TABLE IF NOT EXISTS UNKNOWN_FILES ("
                                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                      "NAME TEXT,"
                                      "PATH TEXT,"
                                      "HASH TEXT"
                                      ");";
        if (err != SQLITE_OK)
        {
            cerr << "Opening error: " << err << endl;
        }
        string delete_known_table = "DELETE FROM KNOWN_FILES;";
        string delete_unknown_table = "DELETE FROM UNKNOWN_FILES;";
        char *errMsg;
        sqlite3_exec(DB, create_known_table.c_str(), nullptr, nullptr, &errMsg);
        sqlite3_exec(DB, create_unknown_table.c_str(), nullptr, nullptr, &errMsg);
        sqlite3_exec(DB, delete_known_table.c_str(), nullptr, nullptr, &errMsg);
        sqlite3_exec(DB, delete_unknown_table.c_str(), nullptr, nullptr, &errMsg);
        // cerr << errMsg << "\n";
    };
    void FillTheDB(FilePtr ourfile);
};
#endif // OUTPUT_DB_H
