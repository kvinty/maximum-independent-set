SHELL:=$(shell which bash)

CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -O3

.PHONY: all test

all: test

test:
	$(CXX) $(CXXFLAGS) \
	-I ../src \
	-I . \
	-o $@ \
	../src/{array,graph,mis}.c \
	mis.cpp \
	$@.cpp
