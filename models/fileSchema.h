#ifndef FILESCHEMA_H_INCLUDED
#define FILESCHEMA_H_INCLUDED

struct File
{
    string name;
    string path;
    string hash_sha1;
    string hash_sha256;
    string hash_md5;
    string hash_crc32;
};

/*
File(string Name, string Path)
{
    name = Name;
    path = Path;
};
~File();

bool GetName() const { return name; };
bool GetPath() const { return path; };
bool GetHash_sha1() const { return hash_sha1; };
bool GetHash_sha256() const { return hash_sha256; };
bool GetHash_md5() const { return hash_md5; };
bool GetHash_crc32() const { return hash_crc32; };
*/

typedef File *FilePtr; // указатель на репозиторий

#endif // FILESCHEMA_H_INCLUDED
