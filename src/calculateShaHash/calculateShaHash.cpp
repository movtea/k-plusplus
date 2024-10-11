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
    SHA1 sha1;
    string hash;

    FileSource fileSource(file->path.c_str(), true,
                          new HashFilter(sha1,
                                         new HexEncoder(
                                             new StringSink(hash), false)));

    for (auto &x : hash)
    {
        x = toupper(x);
    }

    file->hash_sha1 = hash;
}