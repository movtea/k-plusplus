#include "../lib/cryptopp/sha.h"
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/hex.h"
#include <iostream>
#include <string>

using namespace std;

#include "nsrlRepository/nsrlRepository.h"
#include "../models/fileSchema.h"

int main(int argc, char const *argv[])
{
    // setlocale(LC_ALL, "Russian");
    NSRLRepository nsrlRepo = NSRLRepository("./nsrlRepository/test.db");
    File testfile;
    testfile.name = "Test.txt";
    testfile.path = "/home/CLionProjects/k-plusplus/models/fileSchema.h";
    testfile.hash_sha1 = "7691C372B3C494671218EE5C8C56A6D7C53815B7";

    CryptoPP::SHA1 sha1;
    std::string source = "Hello"; // This will be randomly generated somehow
    std::string hash = "";
    CryptoPP::StringSource(source, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
    std::cout << hash;
}
