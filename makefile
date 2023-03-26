all: iterativos sorting
	@echo "Compiling all práctica 1.."
	@echo "End compilation.."

iterativos:
	@echo "Compiling iterative algorithms.."
	g++ -O2 --std=c++11 algoritmo_sin_ordenar.cpp -o algoritmo_sin_ordenar.bin
	g++ -O2 --std=c++11 algoritmo_preordenado.cpp -o algoritmo_preordenado.bin
	@echo "End compilation of iterative algorithms.."

sorting:
	@echo "Compiling sorting algorithms.."
	g++ -O2 --std=c++11 algoritmos_ordenacion.cpp -o algoritmos_ordenacion.bin
	@echo "End compiling sorting algorithms.."

debug:
	@echo "Compiling práctica 1 (debug instrumentation).."
	g++ -g --std=c++11 algoritmo_sin_ordenar.cpp -o algoritmo_sin_ordenar.bin
	g++ -g --std=c++11 algoritmo_preordenado.cpp -o algoritmo_preordenado.bin
	g++ -g --std=c++11 algoritmos_ordenacion.cpp -o algoritmos_ordenacion.bin
	@echo "End compilation (debug instrumentation).."

recursive: sorting
	@echo "Running recursive algorithms with different problem sizes."
	./algoritmos_ordenacion.bin ordenacion_ 0.5 2000 4000 8000 16000 32000 64000

run: all
	./algoritmo_sin_ordenar.bin datos_sin_ordenar.csv 0.5 2000 4000 8000 16000 32000 64000
	./algoritmo_preordenado.bin datos_ordenados.csv 0.5 2000 4000 8000 16000 32000 64000

rundebug: debug
	@echo "Running in debug mode remember to pass params"
	gdb algoritmo_preordenado.bin
	gdb algoritmo_sin_ordenar.bin

docs:
	@echo "Making docs, you need pandoc package"
	pandoc -s -V geometry:margin=1in -o documentation.pdf documentation.md

clean:
	-rm *.bin
