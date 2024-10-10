#ifndef OUTPUT_H
#define OUTPUT_H
#include "../../models/fileSchema.h"
#include "sqlite3.h"
#include "../nsrlRepository/nsrlRepository.h"
#include "../getFileFromDir/getFileFromDir.h"

class OutputDB
{
    private:
     sqlite3 * DB;
     NSRLRepository BIGBALL("test.db");
    public:
     OutputDB()
     {
        sqlite3_open("output.db");
     };
     void FillTheDB(FilePtr File){};
};
#endif 