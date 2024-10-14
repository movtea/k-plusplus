cmake_minimum_required(VERSION 3.30)

project(k-pp)
#add_executable(test ./src/OutputDB/outputDB.cpp)

# задаем директории исходников и библиотек
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

#собираем sqlite3
add_library(sqlite3 STATIC ${LIB_DIR}/sqlite3/sqlite3.c)

#собираем outputdb библиотеку
add_library(OutputDB ${SOURCE_DIR}/OutputDB/outputDB.cpp)
target_link_libraries(OutputDB sqlite3)

# собираем nsrlrepo библиотеку
add_library(nsrlRepository STATIC ${SOURCE_DIR}/nsrlRepository/nsrlRepository.cpp)
target_link_libraries(nsrlRepository sqlite3)

#компиляция getfilefromdir библиотеки
add_library(getFileFromDir STATIC ${SOURCE_DIR}/getFileFromDir/getFileFromDir.cpp)

#добавление cryptopp
add_library(cryptopp STATIC IMPORTED)
set_property(TARGET cryptopp PROPERTY
             IMPORTED_LOCATION ${LIB_DIR}/cryptopp/cryptopp.a)

#компиляция calculateshahash билиотеки
add_library(calculateShaHash STATIC ${SOURCE_DIR}/calculateShaHash/calculateShaHash.cpp)
target_link_libraries(calculateShaHash PRIVATE cryptopp)

#сборка всего приложения
add_executable(main ${SOURCE_DIR}/main.cpp)
target_link_libraries(main calculateShaHash getFileFromDir nsrlRepository OutputDB)
