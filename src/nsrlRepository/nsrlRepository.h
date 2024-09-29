#include "sqlite3.h"
#ifndef NSRLREPO_H_INCLUDED
#define NSRLREPO_H_INCLUDED

class NSRLRepository
{
private:
    sqlite3 *Database;
    bool isOpen = false;

public:
    NSRLRepository();
    ~NSRLRepository() { sqlite3_close(Database); }; // закрытие бд
    bool IsHashInDB(string hash);
    bool GetIsOpen() const { return isOpen; };
};

typedef NSRLRepository *NSRLRepositoryPtr; // указатель на репозиторий

#endif // NSRLREPO_H_INCLUDED
