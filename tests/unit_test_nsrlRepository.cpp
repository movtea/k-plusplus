#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "../src/nsrlRepository/nsrlRepository.h"
#include "../models/fileSchema.h"

bool Test_NSRLRepo_IsHashInDB_1(NSRLRepositoryPtr nsrlRepo)
{
    File testFile;
    testFile.hash_sha1 = "7691C372B3C494671218EE5C8C56A6D7C53815B7";
    nsrlRepo->IsHashInDB(&testFile);
    return testFile.Is_nsrl_db == true;
}

bool Test_NSRLRepo_IsHashInDB_2(NSRLRepositoryPtr nsrlRepo)
{
    File testFile;
    testFile.hash_sha1 = "no";
    nsrlRepo->IsHashInDB(&testFile);
    return testFile.Is_nsrl_db == false;
}

bool Test_NSRLRepo_IsHashInDB_3(NSRLRepositoryPtr nsrlRepo)
{
    File testFile;
    testFile.name = "file";
    nsrlRepo->IsHashInDB(&testFile);
    return testFile.Is_nsrl_db == false;
}

int main(int argc, char const *argv[])
{
    // setlocale(LC_ALL, "Russian");

    //! Разобраться с пространством имён
    try
    {
        NSRLRepository nsrlRepo = NSRLRepository("../src/nsrlRepository/test.db");
        cout << "Тест функции IsHashInDB №1 " << ((Test_NSRLRepo_IsHashInDB_1(&nsrlRepo)) ? "Пройден" : "Не пройден") << endl;
        cout << "Тест функции IsHashInDB №2 " << ((Test_NSRLRepo_IsHashInDB_2(&nsrlRepo)) ? "Пройден" : "Не пройден") << endl;
        cout << "Тест функции IsHashInDB №3 " << ((Test_NSRLRepo_IsHashInDB_3(&nsrlRepo)) ? "Пройден" : "Не пройден") << endl;
    }
    catch (const NSRLRepository::OpenDBException &ex)
    {
        cout << "Ошибка открытия БД SQLite № " << ex.error << endl;
        return 1;
    }

    return 0;
}