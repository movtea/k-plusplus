#include <iostream>
#include <string>
#include "../src/OutputDB/outputDB.h"
#include "../lib/sqlite3/sqlite3.h"
#include "../models/fileSchema.h"

using namespace std;

int main()
{
    OutputDB OurDatabase;
    FilePtr nsrl_file = new File();
    nsrl_file->hash_sha1 = "KNOWN_FILE_TEST_HASH";
    nsrl_file->path = "KNOWN_FILE_TEST_PATH";
    nsrl_file->IsInDB = true;
    OurDatabase.FillTheDB(nsrl_file);

    FilePtr not_nsrl_file = new File();
    not_nsrl_file->hash_sha1 = "UNKNOWN_FILE_TEST_HASH";
    not_nsrl_file->path = "UNKNOWN_FILE_TEST_PATH";
    not_nsrl_file->IsInDB = false;
    OurDatabase.FillTheDB(not_nsrl_file);
};