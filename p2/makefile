K_DIMENSION = 4

all: iterativos dcd
	@echo "Compiling all práctica 2.."
	@echo "End compilation.."

iterativos:
	@echo "Compiling iterative algorithms.."
	g++ -O2 --std=c++11 mainiterativo.cpp -o iterativo.bin
	@echo "End compilation of iterative algorithms.."

dcd:
	@echo "Compiling divide and conquer algorithms.."
	g++ -O2 --std=c++11 maindcdordered.cpp -o dcdoredered.bin
	g++ -O2 --std=c++11 maindcdnotoredered.cpp -o dcdnotordered.bin
	@echo "End compiling sorting algorithms.."
dimension:
	@echo "Compiling dimension problem.."
	g++ -O2 -g --std=c++11 maindimension.cpp -o dimension.bin
	@echo "End compiling dimension problem.."

debug:
	@echo "Compiling práctica 2 (debug instrumentation).."
	g++ -g --std=c++11 mainiterativo.cpp -o iterativo.bin
	g++ -g --std=c++11 maindcdordered.cpp -o dcdoredered.bin
	g++ -g --std=c++11 maindcdnotoredered.cpp -o dcdnotordered.bin
	@echo "End compilation (debug instrumentation).."
# MODE out.csv K_DIMENSION N_POINTS_1 N_POINTS_2 ... N_POINTS_N
run: 
	@echo "Running iterative algorithms problem..."
	./iterativo.bin iterativo $(K_DIMENSION) 5 10 15 20 
	@echo "Running with ordered problem algorithms..."
	./dcdoredered.bin sin_ordenar 0.5 2000 4000 8000 16000 32000 64000
	@echo "Running with oredered problem algorithms..."
	./dcdnotordered.bin ordenado 0.5 2000 4000 8000 16000 32000 64000

rundebug: debug
	@echo "Running in debug mode remember to pass params"
	gdb iterativo.bin
	gdb dcdoredered.bin
	gdb dcdnotordered.bin


docs:
	@echo "Making docs, you need pandoc package"
	pandoc -s -V geometry:margin=1in -o documentation.pdf documentation.md

clean:
	-rm *.bin
