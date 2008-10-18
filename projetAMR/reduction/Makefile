SHELL= bash
TARGET= solve
SRCS= Graph.cpp Solve.cpp
CXXFLAGS = -Wall -g
CXX= g++
LDFLAGS=

all: $(TARGET)

$(TARGET): Solve.o Graph.o
	$(CXX) $(CXXFLAGS) $^ -o $@

solve: Graph.o Solve.o

Graph.o: Graph.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Solve.o: Solve.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	-rm -f $(TARGET) *.o 

polish: clean
	rm -f *.# *.~
