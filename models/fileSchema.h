#ifndef FILESCHEMA_H_INCLUDED
#define FILESCHEMA_H_INCLUDED
#include <string>
using namespace std;

struct File
{
    string name;
    string path;
    string hash_sha1;
    string hash_sha256;
    string hash_md5;
    string hash_crc32;
    bool Is_nsrl_db;
};

typedef File *FilePtr; // указатель на репозиторий

#endif // FILESCHEMA_H_INCLUDED