#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

#include "nsrlRepository.h"

NSRLRepository::NSRLRepository()
{
    int openResult = sqlite3_open(
        "src/nsrlRepository/test.db", // путь к файлу бд
        &Database);                   // открытие бд и передача имени бд open - имя указывается в кодировке

    if (openResult != SQLITE_OK)
    {
        throw OpenDBException(openResult);
    }
}

bool NSRLRepository::IsHashInDB(FilePtr File)
{
    sqlite3_stmt *pStatement;
    // 7691C372B3C494671218EE5C8C56A6D7C53815B7
    /*
        SELECT count(*) FROM FILE WHERE sha1 = "7691C372B3C494671218EE5C8C56A6D7C53815B7";
    */

    int execResult = sqlite3_prepare_v2(Database,
                                        ("SELECT count(*) FROM FILE WHERE sha1 = \"" + File->hash_sha1 + "\"; ").c_str(), // запрос
                                        -1,                                                                               // длина SQL-запроса в символах
                                        &pStatement,
                                        NULL);

    execResult = sqlite3_step(pStatement);
    int n = 0;
    if (execResult == SQLITE_ROW)
    {
        n = sqlite3_column_int(pStatement, 0); // вывод количества записей
    }
    sqlite3_finalize(pStatement);
    // cout << to_string(n) << endl;
    return (n > 0) ? true : false;
}