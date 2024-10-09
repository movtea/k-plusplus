#include <iostream>
#include "output.h"
#include "sqlite3.h"
#include "../../models/fileSchema.h"

void OutputDB:FillTheDB(FilePtr File)
{
    sqlite3_stmt* stmt;
    string hash = File->hash_md5;
    string path = File->path;
    if (IsHashInDB(File) == true)
    {
        string sql = "INSERT INTO KNOWN_FILES (hash,path)"
                            "VALUES (:hash, :path);";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":hash"), hash, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":path"), path, -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    else
    {
        string sql = "INSERT INTO UNKNOWN_FILES (hash,path)"
                            "VALUES (:hash, :path);";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":hash"), hash, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":path"), path, -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}