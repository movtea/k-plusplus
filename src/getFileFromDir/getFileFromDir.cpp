#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;

#include "../../models/fileSchema.h"
#include "getFileFromDir.h"

namespace fs = filesystem;

vector<FilePtr> getFileFromDir(string path)
{
    vector<FilePtr> result;

    for (const auto &dirEntry : fs::recursive_directory_iterator(path))
    {
        if (!fs::is_directory(dirEntry.path()))
        {
            FilePtr file = new File();
            file->path = dirEntry.path();
            file->name = dirEntry.path().filename();
            result.push_back(file);
        }
    }
    return result;
}