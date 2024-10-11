#include <iostream>
#include <vector>
#include <string>
#include "../src/calculateShaHash/calculateShaHash.h"

using namespace std;

bool Test_CalculateSHA1Hash_1()
{
    File testFile;
    testFile.name = "System.Speech.dll";
    testFile.path = "/home/dmitriy/CLionProjects/k-plusplus/tests/System.Speech.dll";

    CalculateSHA1Hash(&testFile);

    return testFile.hash_sha1 == "7691C372B3C494671218EE5C8C56A6D7C53815B7";
}

int main(int argc, char const *argv[])
{

    cout << "Тест функции CalculateSHA1Hash №1 " << ((Test_CalculateSHA1Hash_1()) ? "Пройден" : "Не пройден") << endl;
}