SHELL= bash
TARGET= main
OBJS= Graph.o Main.o #Tree.o
CXXFLAGS = -Wall -g
CXX= g++
LDFLAGS=

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

Graph.o: Graph.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Tree.o: Tree.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(TARGET) *.o 

polish: clean

