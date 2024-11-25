#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>

using namespace std;
using namespace filesystem;

#include "../../models/fileSchema.h"
#include "getFileFromDir.h"

/**
 * @param [in] path Путь к анализируемой директории
 * @param [out] result Заполнены вектор со считанными именами и путями в собственных структурах для каждого файла
 */
vector<FilePtr> getFileFromDir(filesystem::path path)
{
    vector<FilePtr> result;
    for (const auto &dirEntry : recursive_directory_iterator(path, directory_options::skip_permission_denied))
    {
        filesystem::path filePath = dirEntry.path();
        filesystem::path fileName = dirEntry.path().filename();

        try
        {
            if (!is_directory(dirEntry) && exists(dirEntry))
            {
                FilePtr file = new File();
                file->path = filePath.string();
                file->name = fileName.string();
                result.push_back(file);
                //cout << "Считывание:" << file->path  <<
                //     " Файл номер: " << result.size() << endl;
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
