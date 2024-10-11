#include "sqlite3.h"
#ifndef NSRLREPO_H_INCLUDED
#define NSRLREPO_H_INCLUDED

#include "../../models/fileSchema.h"

class NSRLRepository
{
private:
    sqlite3 *Database;

public:
    class OpenDBException // Для проброса ошибок открытия БД
    {
    public:
        int error;
        OpenDBException(int Error) { error = Error; };
    };
    NSRLRepository(string path);
    ~NSRLRepository() { sqlite3_close(Database); }; // закрытие бд
    void IsHashInDB(FilePtr file);
};

typedef NSRLRepository *NSRLRepositoryPtr; // указатель на репозиторий

#endif // NSRLREPO_H_INCLUDED