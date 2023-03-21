all: 
	g++ -O2 --std=c++11 practica1algoritmos.cpp -o practica1.bin

debug: 
	g++ -g --std=c++11 practica1algoritmos.cpp -o practica1-debug.bin

clean:
	-rm practica1.bin
	-rm practica1-debug.bin