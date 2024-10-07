#include <iostream>
#include <vector>
#include <string>
#include "../src/getFileFromDir/getFileFromDir.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<FilePtr> filename  = getFileFromDir("/home/shvabriq/Загрузки/filesystem-master/k-plusplus");

    for(int i = 0; i < filename.size(); i++)
    {
        cout << filename[i]->name<< endl;
        cout << filename[i]->path<< endl;
    }
    
    filename.clear();
    return 0;
}