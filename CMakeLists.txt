cmake_minimum_required(VERSION 3.30)

project(k-pp)
#add_executable(test ./src/OutputDB/outputDB.cpp)

# задаем директории исходников и библиотек
set(SOURCE_DIR ./src)
set(LIB_DIR ./lib)

#собираем sqlite3
add_library(sqlite3 STATIC ${LIB_DIR}/sqlite3/sqlite3.c)

#собираем outputdb как библиотека
add_library(OutputDB ${SOURCE_DIR}/OutputDB/outputDB.cpp)
target_link_libraries(OutputDB sqlite3)