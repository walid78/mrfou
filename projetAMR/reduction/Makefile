SHELL= bash
TARGET= solve
SRCS= Graph.cpp Solve.cpp Cover.cpp
CXXFLAGS = -Wall -g
CXX= g++
LDFLAGS=

all: $(TARGET)

$(TARGET): Solve.o Graph.o Cover.o
	$(CXX) $(CXXFLAGS) $^ -o $@

solve: Graph.o Solve.o Cover.o

Graph.o: Graph.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Cover.o: Cover.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Solve.o: Solve.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	-rm -f $(TARGET) *.o 

polish: clean
	rm -f *# *~
