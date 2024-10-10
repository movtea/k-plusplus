#ifndef OUTPUT_DB_H
#define OUTPUT_DB_H

#include "../../lib/sqlite3/sqlite3.h"
#include "../../models/fileSchema.h"
#include <iostream>

using namespace std;

class OutputDB
{
    private:
        sqlite3 *DB;
    public:
        OutputDB()
        {
            sqlite3_open("output.db", &DB);
            string create_known_table = "CREATE TABLE KNOWN_FILES ("
                                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "HASH TEXT,"
                                "PATH TEXT"
                                ");";
            string create_unknown_table = "CREATE TABLE UNKNOWN_FILES ("
                                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "HASH TEXT,"
                                "PATH TEXT"
                                ");";            
            char *errMsg;
            sqlite3_exec(DB, create_known_table.c_str(), nullptr, nullptr, &errMsg);
            sqlite3_exec(DB,create_unknown_table.c_str(),nullptr,nullptr,&errMsg);
            cout << errMsg << "\n";
        };
        void FillTheDB(FilePtr ourfile);
};
#endif //OUTPUT_DB_H