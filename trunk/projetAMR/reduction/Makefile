SHELL= bash
TARGET= solve
OBJS= Graph.o Solve.o HamilCircuit.o KCol.o Clique.o VertexCover.o IndepSet.o MinisatBuilder.o
CXXFLAGS = -Wall -g
CXX= g++
LDFLAGS=
MINISAT_DIR= minisat/simp

all: minisat gengraph $(TARGET)

minisat:
	@echo -e "\033[31mUnzipping minisat\033[0m"
	unzip minisat2-070721.zip
	@echo -e "\033[31mCompilation minisat\033[0m"
	@(cd $(MINISAT_DIR) && $(MAKE) rs)
	@echo -e "\033[31mCompilation Reductions : solve\033[0m"
	@(mv $(MINISAT_DIR)/minisat_static $(MINISAT_DIR)/minisat)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

Graph.o: Graph.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Solve.o: Solve.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

HamilCircuit.o: HamilCircuit.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

MinisatBuilder.o: MinisatBuilder.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

KCol.o: KCol.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Clique.o: Clique.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

VertexCover.o: VertexCover.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

IndepSet.o: IndepSet.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(TARGET) *.o 

polish: clean
	rm -f *# *~ gengraph/gengraph
	rm -Rf minisat/
