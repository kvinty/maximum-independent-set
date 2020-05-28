.PHONY: all build test clean

CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -O3

all: build

build:
	swig -c++ -python mis.i

	$(CXX) $(CXXFLAGS) \
	-fPIC -shared -I ../src `pkg-config --cflags python3` -o _mis.so \
	../src/array.c ../src/graph.c ../src/mis.c mis_wrap.cxx mis.cxx

	rm mis_wrap.cxx

test:
	./test.py

clean:
	rm --force mis_wrap.cxx mis.py _mis.so
