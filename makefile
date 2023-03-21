all: 
	@echo "Compiling práctica 1.."
	g++ -O2 --std=c++11 algoritmo_sin_ordenar.cpp -o algoritmo_sin_ordenar.bin
	g++ -O2 --std=c++11 algoritmo_preordenado.cpp -o algoritmo_preordenado.bin
	@echo "End compilation.."

debug:
	@echo "Compiling práctica 1 (debug instrumentation).."
	g++ -g --std=c++11 algoritmo_sin_ordenar.cpp -o algoritmo_sin_ordenar.bin
	g++ -g --std=c++11 algoritmo_preordenado.cpp -o algoritmo_preordenado.bin
	@echo "End compilation (debug instrumentation).."

run: all
	./algoritmo_sin_ordenar.bin datos_sin_ordenar.csv 0.5 2000 4000 8000 16000 32000 64000
	./algoritmo_preordenado.bin datos_ordenados.csv 0.5 2000 4000 8000 16000 32000 64000

rundebug: debug
	@echo "Running in debug mode remember to pass params"
	gdb algoritmo_preordenado.bin
	gdb algoritmo_sin_ordenar.bin

docs:
	@echo "Making docs, you need pandoc package"
	pandoc -s -V geometry:margin=1in -o documentation.pdf respuestas.md

clean:
	-rm *.bin
