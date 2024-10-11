#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "nsrlRepository/nsrlRepository.h"
#include "getFileFromDir/getFileFromDir.h"
#include "OutputDB/outputDB.h"
#include "calculateShaHash/calculateShaHash.h"
#include "../models/fileSchema.h"

int main(int argc, char const *argv[])
{
    // setlocale(LC_ALL, "Russian");
    vector<FilePtr> filename = getFileFromDir("/home/dmitriy/CLionProjects/k-plusplus/tests");
    NSRLRepository nsrlRepo = NSRLRepository("./nsrlRepository/test.db");
    OutputDB ourDatabase;

    for (int i = 0; i < filename.size(); i++)
    {
        CalculateSHA1Hash(filename[i]);
        nsrlRepo.IsHashInDB(filename[i]);
        ourDatabase.FillTheDB(filename[i]);
    }
    filename.clear();
}
