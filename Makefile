CPPFLAGS=-Wall -g
CXX=g++

all: assignment_1

assignment_1: main.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

recycle:
	tail -n +30 chris.out > recin.txt
