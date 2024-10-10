#include <iostream>
#include "output.h"
#include "sqlite3.h"
#include "../../models/fileSchema.h"
#include "../nsrlRepository/nsrlRepository.h"
#include "../getFileFromDir/getFileFromDir.h"

void OutputDB::FillTheDB(FilePtr file)
{
    sqlite3_stmt *stmt;
    if (file->IsINDB == true)
    {
        string sql = "INSERT INTO KNOWN_FILES (hash,path)"
                     "VALUES (:hash, :path);";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":hash"), file->hash_sha1.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":path"), file->path.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    else
    {
        string sql = "INSERT INTO UNKNOWN_FILES (hash,path)"
                     "VALUES (:hash, :path);";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":hash"), file->hash_sha1.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":path"), file->path.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    };
};
