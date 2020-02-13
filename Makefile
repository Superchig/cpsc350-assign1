CPPFLAGS=-Wall -g
CXX=g++

all: assign_1

assign_1: main.cpp
	$(CXX) $(CPPFLAGS) $< -o $@