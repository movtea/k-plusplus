cmake_minimum_required(VERSION 3.10)

project(kpp)
#add_executable(test ./src/OutputDB/outputDB.cpp)

# задаем директории исходников и библиотек
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchains/windows.txt)
    message(STATUS "Compiling for Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Compiling for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Compiling for MacOS")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchains/macos.cmake)
endif()

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
#add_library(cryptopp STATIC IMPORTED)
#set_property(TARGET cryptopp PROPERTY
#ls             IMPORTED_LOCATION ${LIB_DIR}/cryptopp/cryptlib.lib)

add_subdirectory(${LIB_DIR}/cryptopp-cmake)

#компиляция calculateshahash билиотеки
add_library(calculateShaHash STATIC ${SOURCE_DIR}/calculateShaHash/calculateShaHash.cpp)
target_link_libraries(calculateShaHash PRIVATE cryptopp)

#сборка всего приложения
add_executable(k-pp ${SOURCE_DIR}/main.cpp)
target_link_libraries(k-pp calculateShaHash getFileFromDir nsrlRepository OutputDB)

#отправим собранное приложение в необходимую директорию
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
