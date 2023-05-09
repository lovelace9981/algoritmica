all: run
	@echo "Executing all"

build_arista: 
	@echo "Compiling arista heuristic"
	g++ -o programa.bin main.cpp stock.cpp
	
build: build_arista build_adjacency
	@echo "Compiling all"
	
run: build
	@echo "Running programa.bin"
	@echo "Running edge heuristic"
	./programa.bin
	
rm: 
	-rm arista.bin
	-rm adjacency.bin