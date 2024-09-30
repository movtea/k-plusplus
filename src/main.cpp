#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "nsrlRepository/nsrlRepository.h"
#include "../models/fileSchema.h"

int main(int argc, char const *argv[])
{
    // setlocale(LC_ALL, "Russian");
    NSRLRepository nsrlRepo;
    File testfile;
    testfile.name = "Test.txt";
    testfile.path = "/home/CLionProjects/k-plusplus/models/fileSchema.h";
    testfile.hash_sha1 = "7691C372B3C494671218EE5C8C56A6D7C53815B7";
}
