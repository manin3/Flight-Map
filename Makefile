
EXECNAME=final
CXX=g++
CXXFLAGS=-g -Wall -pedantic
CLANG=clang++
OTHERFLAGS = -I.    -std=c++1y -stdlib=libc++ -lc++abi
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

SRC=Loader.cpp main.cpp

ODIR=objsLDIR=../libc
LIBS=-lm
TEST_OBJS= catch.o tests.o

all :  main Graph airport_Map
	$(CXX)  main.o Graph.o airport_Map.o -o $(EXECNAME) -std=c++11
main : main.cpp
	$(CXX) -c main.cpp -o main.o -std=c++11
Graph : Graph.cpp
	$(CXX) -c Graph.cpp -o Graph.o -std=c++11
airport_Map : airport_Map.cpp
	$(CXX) -c airport_Map.cpp -o airport_Map.o -std=c++11
test: catch/catchmain.cpp tests/test1.cpp airport_Map.cpp Graph.cpp
	$(CLANG) catch/catchmain.cpp tests/test1.cpp airport_Map.cpp Graph.cpp $(LDFLAGS) -o test
clean :
	rm -rf *.o exec
.PHONY: test