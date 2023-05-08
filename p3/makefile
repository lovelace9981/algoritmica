all: run
	@echo "Executing all"

build_arista: 
	@echo "Compiling arista heuristic"
	g++ -o arista.bin main_edge.cpp nodo.cpp euler2.cpp

build_adjacency:
	@echo "Compiling adjacency heuristic"
	g++ -o adjacency.bin main_adjacency.cpp euler.cpp
	
build: build_arista build_adjacency
	@echo "Compiling all"
	
run: build
	@echo "Running programa.bin"
	@echo "Running edge heuristic"
	./arista.bin grafoEjemplo.graph
	@echo "Running edge heuristic 2"
	./arista.bin grafoEjemplo2.graph
	@echo "Running adjacency heuristic 1"
	./adjacency.bin matrix_heuristic.txt adjacencymatrixnotoddej1.matrix
	@echo "Running adjacency heuristic 2"
	./adjacency.bin matrix_heuristic.txt adjacencymatrixnotoddej2.matrix
	
rm: 
	-rm arista.bin
	-rm adjacency.bin