cmake_minimum_required(VERSION 3.30)

project(k-pp)
#add_executable(test ./src/OutputDB/outputDB.cpp)

set(SOURCE_CODE ./src/OutputDB/outputDB.cpp)
set(SOURCE_LIB ./lib/sqlite3/sqlite3.c)

add_library(sqlite3 STATIC ${SOURCE_LIB})
add_executable(test ${SOURCE_CODE})

target_link_libraries(test sqlite3)