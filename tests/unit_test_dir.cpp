#include <iostream>
#include <vector>
#include <string>
#include "../src/getFileFromDir/getFileFromDir.h"

using namespace std;

// bool Test_GetFileFromDir_1()
// {
//     File testFile1;
//     testFile1.name = "getFileFromDir.cpp";
//     testFile1.path = "/home/shvabriq/Загрузки/filesystem-master/k-plusplus/src/getFileFromDir/getFileFromDir.cpp";

//     File testFile2;
//     testFile2.name = "getFileFromDir.h";
//     testFile2.path = "/home/shvabriq/Загрузки/filesystem-master/k-plusplus/src/getFileFromDir/getFileFromDir.h";

//     File testFile3;
//     testFile3.name = "getFileFromDir.h";

//     vector<FilePtr> filename  = getFileFromDir("/home/shvabriq/Загрузки/filesystem-master/k-plusplus");

//     vector<FilePtr> testvector;
//     testvector.push_back(&testFile1);
//     testvector.push_back(&testFile2);

//     vector<FilePtr> testvector1;
//     testvector1.push_back(&testFile1);
//     testvector1.push_back(&testFile3);


//     for(int i = 0; i < testvector.size(); i++)
//     {
//         cout << testvector[i]->name<< endl;
//         cout << testvector[i]->path<< endl;
//     }

//     return testvector == testvector1;
// }


int main(int argc, char const *argv[])
{

    // cout << "Тест функции GetFileFromDir №1 " << ((Test_GetFileFromDir_1()) ? "Пройден" : "Не пройден") << endl;
    vector<FilePtr> filename  = getFileFromDir("/home/shvabriq/Загрузки/filesystem-master/k-plusplus");

    for(int i = 0; i < filename.size(); i++)
    {
        cout << filename[i]->name<< endl;
        cout << filename[i]->path<< endl;
    }
    
    filename.clear();
    return 0;
}