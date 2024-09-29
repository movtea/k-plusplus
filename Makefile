all: k-pp

k-pp: sqlite3.o  main.o 
	g++ ./build/main.o ./build/sqlite3.o -o build/k-pp

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp -o build/main.o

sqlite3.o: ./lib/sqlite3.c
	gcc -c ./lib/sqlite3.c -o build/sqlite3.o

