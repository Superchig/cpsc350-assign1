CPPFLAGS=-Wall -g
CXX=g++

all: assignment1.exe

assignment1.exe: main.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

recycle:
	tail -n +30 chris.out > recin.txt
