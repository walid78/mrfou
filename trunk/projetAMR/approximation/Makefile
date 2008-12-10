SHELL= bash
TARGET= main
OBJS= Graph.o Main.o Tree.o  timing.o
CXXFLAGS = -Wall -g
CXX= g++-4.2
CC=gcc
LDFLAGS=

all: $(TARGET) #clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

timing.o: timing.cc
	$(CC) $(CXXFLAGS) -c $< -o $@

Graph.o: Graph.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Tree.o: Tree.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o 

polish: clean
	rm -f $(TARGET)
