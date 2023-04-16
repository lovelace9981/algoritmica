#include <iostream>
#include "dcdnotordered.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>

#define DEBUG_PARAMS_PRINT

using namespace std ;

int main(int argc, char *argv[]){

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida semilla K_SIZE tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Argumento 1 = fichero
	// Argumento 2 = semilla
	// Argumento 3 = k_dimension
	// Argumento 4..n = numero de puntos
	int k_dimension = atoi(argv[3]);
	int tamanio_caso = 0;
	DCD<int>* no_dominados_ptr;

	fsalida << "n " << "T(n) " << "K " << "TE(n)\n" ;
	for (int i = 4 ; i < argc; i++){
		tamanio_caso = atoi(argv[i]);
        // no_dominados_ptr = new DCD<int>(k_dimension, tamanio_caso);
		//Escribimos los nombres de las columnas del output

		// Inicializamos generador de no. aleatorios
		semilla= atoi(argv[2]);
		
		srand(semilla);

		// CREAMOS clase de no_dominados, punto maximo 10
		no_dominados_ptr = new DCD<int>(k_dimension, tamanio_caso, 100);
		cerr << "Ejecutando algoritmo recursivo DyV para tam " << tamanio_caso << endl ;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		//Ejecutamos algoritmo iterativo
		no_dominados_ptr -> divandconqCall();
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< tamanio_caso <<endl;

		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<< tamanio_caso<<" "<<tejecucion<<"\n";

		// #ifdef DEBUG_PARAMS_PRINT
		// cout << tamanio_caso << endl ;
		// 	no_dominados_ptr -> print_problem();
		// #endif

		delete no_dominados_ptr;
	}
		
	// Cerramos fichero de salida
	fsalida.close();


}