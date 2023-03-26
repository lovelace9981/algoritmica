#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include "algoritmos.hpp"

using namespace std;

int main(int argc, char *argv[]){
    vector<int> aleatorios_casos;
    APO<int> arbol;

	int n, argumento,actual_elem;
	argumento = argc - 3;

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
    unsigned long tejecucion;
	ofstream fsalida;
	ofstream fsalida2;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	string merge = string(argv[1]) + "merge.csv";
	string heapsort = string(argv[1]) + "heapsort.csv";
	fsalida.open(heapsort);
	fsalida2.open(merge);

	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	//Escribimos los nombres de las columnas del output
	fsalida << "n " << "T(n) " << "K " << "TE(n)\n" ;
	fsalida2 << "n " << "T(n) " << "K " << "TE(n)\n" ;


	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);

	// Pasamos por cada tamanio de caso para el ejercicio 1
	for (int i = 0; i < argumento; i++){
		n = atoi(argv[i+3]);
		
		//Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (int j = 0; j<n; j++){
            actual_elem = rand() % n;
            aleatorios_casos.push_back(actual_elem);
        }

		arbol = aleatorios_casos;

			
		cerr << "Ejecutando algoritmo HeapSort para tam " << n << endl ;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
        
		//Ejecutamos algoritmo ejercicio 2
        arbol.HeapSort();

		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n << endl;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida << n << " " << tejecucion << "\n";
    
        cerr << "Ejecutando algoritmo MergeSort para tam " << n << endl ;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
        
        mergeSort(aleatorios_casos, 0, aleatorios_casos.size());

		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n << endl;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida2 << n << " " << tejecucion << "\n";
		
	

        // cout << "HeapSort" << endl;
        // arbol.printVectorOrdenado();
        // cout << "MergeSort" << endl;
        // for(int i = 0; i < aleatorios_casos.size(); i++){
        //     cout << aleatorios_casos[i] << " ";
        // }
        // cout << "\n";

        // Liberamos memoria del vector
		aleatorios_casos.clear();
    }
    // Cerramos fichero de salida
	fsalida.close();
}