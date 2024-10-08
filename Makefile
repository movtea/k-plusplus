all: k-pp

k-pp: sqlite3.o nsrlRepository.o  main.o 
	g++ ./build/main.o ./build/nsrlRepository.o ./build/sqlite3.o -o build/k-pp

main.o: ./src/main.cpp
	g++ -c ./src/main.cpp -o build/main.o

nsrlRepository.o: ./src/nsrlRepository/nsrlRepository.cpp
	g++ -c ./src/nsrlRepository/nsrlRepository.cpp -o build/nsrlRepository.o


sqlite3.o: ./lib/sqlite3.c
	gcc -c ./lib/sqlite/sqlite3.c -o build/sqlite3.o

testNSRL: sqlite3.o nsrlRepository.o
	g++ ./tests/unit_test_nsrlRepository.cpp ./build/nsrlRepository.o ./build/sqlite3.o -o build/testNSRL

dir.o: 
	g++ -c ./src/getFileFromDir/getFileFromDir.cpp -o build/dir

testDIR: dir.o
	g++ ./tests/unit_test_dir.cpp ./build/dir -o build/testDIR

runTestDIR: testDIR
	./build/testDIR