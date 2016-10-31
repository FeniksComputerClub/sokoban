Board.o: Board.h BitBoard.h sys.h Index.h Board.cxx 
	g++ -std=c++11 -c Board.cxx -o Board.o

test.o: test.cxx
	g++ -std=c++11 -c test.cxx -o test.o

test: test.o Board.o
	g++ test.o Board.o -o test
