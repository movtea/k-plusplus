#include <fstream>
#include <string>
#include <cctype>
#include "../../lib/cryptopp/cryptlib.h"
#include "../../lib/cryptopp/sha.h"
#include "../../lib/cryptopp/hex.h"
#include "../../lib/cryptopp/filters.h"
#include "../../lib/cryptopp/files.h"
#include "../../models/fileSchema.h"

#include "calculateShaHash.h"

using namespace std;
using namespace CryptoPP;

void CalculateSHA1Hash(FilePtr file)
{
    SHA256 sha256;
    string hash;

    try
    {
        FileSource fileSource(file->path.c_str(), true,
                              new HashFilter(sha256,
                                             new HexEncoder(
                                                 new StringSink(hash))));
        file->hash_sha1 = hash;
        //cout << "Хэш файла "+file->path+": " << hash << endl;
    }
    catch (const exception &e)
    {
        cerr << "Another error :( :" << ": " << e.what() << endl;
        file->hash_sha1 = "";
    }
}
