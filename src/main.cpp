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

    if (nsrlRepo.GetIsOpen())
    {
        cout << "Оно открыто))))\n";
        nsrlRepo.IsHashInDB("7691C372B3C494671218EE5C8C56A6D7C53815B7");
    }
    return 0;
}
