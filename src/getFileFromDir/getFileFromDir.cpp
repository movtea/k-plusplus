#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

using namespace std;
using namespace filesystem;

#include "../../models/fileSchema.h"
#include "getFileFromDir.h"

vector<FilePtr> getFileFromDir(string path)
{
    vector<FilePtr> result;
    for (const auto &dirEntry : recursive_directory_iterator(path))
    {
        filesystem::path filePath = dirEntry.path();
        filesystem::path fileName = dirEntry.path().filename();

        try
        {
            if (!is_directory(dirEntry) && exists(dirEntry))
            {
                ifstream IsFileOpen(filePath);

                if (!IsFileOpen.is_open())
                {
                    cerr << "Can't open the file (permisson denied): " << filePath << endl;
                    continue;
                }

                FilePtr file = new File();
                file->path = filePath.string();
                file->name = fileName.string();
                result.push_back(file);
            }
        }
        catch (const filesystem_error &e)
        {
            cerr << "Filesystem error: " << fileName << ": " << e.what() << endl;
        }
        catch (const exception &e)
        {
            cerr << "Another error :( :" << fileName << ": " << e.what() << endl;
        }
    }
    return result;
}