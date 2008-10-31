
SHELL= bash
TARGET= solve
OBJS= Graph.o Solve.o Cover.o CircuitHamiltonien.o  KCol.o #MinisatBuilder.o
CXXFLAGS = -Wall -g
CXX= g++
LDFLAGS=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

Graph.o: Graph.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Cover.o: Cover.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Solve.o: Solve.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

CircuitHamiltonien.o: CircuitHamiltonien.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

MinisatBuilder.o: MinisatBuilder.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

KCol.o: KCol.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(TARGET) *.o 

polish: clean
	rm -f *# *~
