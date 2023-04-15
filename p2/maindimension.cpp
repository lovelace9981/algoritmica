#include <iostream>
#include "dcddimension.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>

#define DEBUG_PARAMS_PRINT

using namespace std ;

int main(int argc, char *argv[]){
	int n, argumento;
	argumento = argc - 3;

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida K_SIZE tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	int k_dimension = atoi(argv[2]);
	int n_problemas = argc - 3;
	int tamanio_caso = 0;
	DCDDIMENSION<double>* no_dominados_ptr;

	for (int i = 0; i < n_problemas; i++){
		tamanio_caso = atoi(argv[i+3]);
		// CREAMOS clase de no_dominados, punto maximo 10
		no_dominados_ptr = new DCDDIMENSION<double>(k_dimension, tamanio_caso, 10);
        no_dominados_ptr -> print_problem() ;

		//Escribimos los nombres de las columnas del output
		fsalida << "n " << "T(n) " << "K " << "TE(n)\n" ;

		// Inicializamos generador de no. aleatorios
		semilla= atoi(argv[2]);
		srand(semilla);

		cerr << "Ejecutando algoritmo recursivo dimension para tam " << n << endl ;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		//Ejecutamos algoritmo iterativo
		no_dominados_ptr -> puntos_no_dominados();
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< tamanio_caso <<endl;

		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";

		#ifdef DEBUG_PARAMS_PRINT
		no_dominados_ptr -> print_problem();
		#endif

		delete no_dominados_ptr;
	}
		
	// Cerramos fichero de salida
	fsalida.close();


}