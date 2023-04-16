all: iterativos dcd dimension
	@echo "Compiling all práctica 2.."
	@echo "End compilation.."

iterativos:
	@echo "Compiling iterative algorithms.."
	g++ -O2 --std=c++11 mainiterativo.cpp -o iterativo.bin
	@echo "End compilation of iterative algorithms.."

dcd:
	@echo "Compiling divide and conquer algorithms.."
	g++ -O2 --std=c++11 maindcdnotordered.cpp -o dcdnotordered.bin
	@echo "End compiling sorting algorithms.."
dimension:
	@echo "Compiling dimension problem.."
	g++ -O2 --std=c++11 maindimension.cpp -o dimension.bin
	@echo "End compiling dimension problem.."

debug:
	@echo "Compiling práctica 2 (debug instrumentation).."
	g++ -g --std=c++11 mainiterativo.cpp -o iterativo.bin
	g++ -g --std=c++11 maindcdordered.cpp -o dcdnotordered.bin
	g++ -g --std=c++11 maindimension.cpp -o dimension.bin
	@echo "End compilation (debug instrumentation).."
# MODE out.csv K_DIMENSION N_POINTS_1 N_POINTS_2 ... N_POINTS_N
run: clean all
	@echo "Running all the algorithms with the same sizes"
	./iterativo.bin ./output/iterativo.txt 0 10 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536
	./dcdnotordered.bin ./output/dyv.txt 0 10 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536
	./dimension.bin ./output/dimension.txt 0 10 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536

rundebug: debug
	@echo "Running in debug mode remember to pass params"
	gdb iterativo.bin
	gdb dcdoredered.bin
	gdb dcdnotordered.bin


docs:
	@echo "Making docs, you need pandoc package"
	pandoc -s -V geometry:margin=1in -o documentation.pdf documentation.md

clean:
	@echo "Cleaning all the files.."
	-rm *.bin
	-rm *.txt
