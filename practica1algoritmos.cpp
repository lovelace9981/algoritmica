#include <iostream>
#include "algoritmos.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>

using namespace std ;


int main(int argc, char *argv[]){
	/* Vectores de entrada de prueba del ejercicio*/
	// 5 1 9 2 2 5 1 1 7
	// 1 1 1 2 2 5 5 7 9
	vector<int> ejercicio1 = {5,1,9,2,2,5,1,1,7};
    vector<int> vectorFinal;
	vector<int> ejercicio2 = {1,1,1,2,2,5,5,7,9};
    vector<int> aleatorios_casos;
	
	int n, i, argumento;
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
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);



	// Pasamos por cada tamanio de caso para el ejercicio 1
	for (argumento = 0; argumento < argc; argumento++) {
		//Cogemos el tamanio del caso
		n = atoi(argv[argumento+3]);
		
		//Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			aleatorios_casos.push_back(rand()%n);

		mergeSort(aleatorios_casos, 0, n);

		cerr << "Ejecutando algoritmo ejercicio 1 para tam " << n << endl ;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
        //Ejecutamos algoritmo ejercicio 1
        // vectorSinRepeticion(ejercicio1, vectorFinal, ejercicio1.size());
		repetidosEficienteOrdenado(aleatorios_casos, vectorFinal, ejercicio2.size());

		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;

		// for (int i = 0; i < vectorFinal.size(); i++)
		// 	cout << vectorFinal[i] << " ";
        // cout << endl ;

        // Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		aleatorios_casos.empty();
    }
    // Cerramos fichero de salida
	fsalida.close();
}