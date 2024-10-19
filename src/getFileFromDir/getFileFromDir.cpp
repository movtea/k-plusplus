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
            std::filesystem::path path_from_dir = dirEntry.path();
            file->path = path_from_dir.string();
            std::filesystem::path filename_from_dir = dirEntry.path().filename();
            file->name = filename_from_dir.string();
            result.push_back(file);
        }
    }
    return result;
}