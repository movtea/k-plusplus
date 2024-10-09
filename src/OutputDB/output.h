#ifndef OUTPUT_H
#define OUTPUT_H
#include "../../models/fileSchema.h"
#include "sqlite3.h"

class OutputDB
{
    private:
     sqlite3 * DB;
    public:
     OutputDB()
     {
        sqlite3_open("output.db");
     };
     void FillTheDB(FilePtr File){};
};
#endif 