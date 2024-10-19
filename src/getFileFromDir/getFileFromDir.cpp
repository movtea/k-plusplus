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

    try
    {
        for (const auto &dirEntry : recursive_directory_iterator(path))
        {
            std::filesystem::path filePath = dirEntry.path();
            std::filesystem::path fileName = dirEntry.path().filename();

            if (!is_directory(dirEntry) && exists(dirEntry) && !is_block_file(dirEntry) && (temp_directory_path() != filePath))
            {
                ifstream IsFileOpen(filePath);

                if (!IsFileOpen.is_open())
                {
                    cerr << "Не удалось открыть файл (permisson denied): " << filePath << endl;
                    continue;
                }

                FilePtr file = new File();
                file->path = filePath.string();
                file->name = fileName.string();
                result.push_back(file);
            }
        }
    }
    catch (const filesystem_error &e)
    {
        cerr << "Ошибка filesystem: " << e.what() << endl;
    }
    return result;
}