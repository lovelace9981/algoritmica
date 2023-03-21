#include <iostream>
#include "algoritmos.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>

using namespace std ;


int main(int argc, char *argv[]){
    vector<int> vectorFinal;
    vector<int> aleatorios_casos;
	
	int n, argumento;
	argumento = argc - 3;

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

	//Escribimos los nombres de las columnas del output
	fsalida << "n " << "T(n) " << "K " << "TE(n)\n" ;
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);
	// Pasamos por cada tamanio de caso para el ejercicio 1
	for (int i = 0; i < argumento; i++){
		n = atoi(argv[i+3]);
		
		//Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (int j = 0; j<n; j++)
			aleatorios_casos.push_back(rand()%n);


		cerr << "Ejecutando algoritmo ejercicio 1 para tam " << n << endl ;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
       
	    //Ejecutamos algoritmo ejercicio 1
        vectorSinRepeticion(aleatorios_casos, vectorFinal, n);
		
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;

		// for (int i = 0; i < vectorFinal.size(); i++)
		// 	cout << vectorFinal[i] << " ";
        // cout << endl ;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		aleatorios_casos.clear();
		vectorFinal.clear();
    }
    // Cerramos fichero de salida
	fsalida.close();
}