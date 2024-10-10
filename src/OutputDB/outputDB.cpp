#include <iostream>
#include "outputDB.h"

using namespace std;
void OutputDB::FillTheDB(FilePtr ourfile)
{
    if (ourfile->IsInDB == true)
    {
        sqlite3_stmt* stmt;
        string sql = "INSERT INTO KNOWN_FILES (HASH,PATH) VALUES ('"+ourfile->hash_sha1+"','"+ourfile->path+"');";
        cout << sql << "\n";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    else
    {
        sqlite3_stmt* stmt;
        string sql = "INSERT INTO UNKNOWN_FILES (HASH,PATH) VALUES ('"+ourfile->hash_sha1+"','"+ourfile->path+"');";
        //cout << sql << "\n";
        sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    };
};

int main()
{
    OutputDB OurDatabase;
    FilePtr nsrl_file = new File();
    nsrl_file->hash_sha1 = "TEST_HASH";
    nsrl_file->path = "TEST_PATH";
    nsrl_file->IsInDB = true;
    OurDatabase.FillTheDB(nsrl_file);

    FilePtr not_nsrl_file = new File();
    not_nsrl_file->hash_sha1 = "TEST_HASH";
    not_nsrl_file->path = "TEST_PATH";
    not_nsrl_file->IsInDB = false;
    OurDatabase.FillTheDB(not_nsrl_file);
}