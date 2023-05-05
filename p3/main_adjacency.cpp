#include "euler.hpp"
#include <chrono>
#include <cstdlib>

int main(int argc, char **argv){
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución

    if (argc < 3){
        cerr << "Error en la entrada de parámetros!" << endl;
        cerr << argv[0] << " <fichero_salida> " << "<matriz_de_adyacencia>"  << endl;
        terminate();
    }
    ofstream fsalida;

    // Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
    string file_matrix = argv[2];

    // Euler e("adjacencymatrix");
    // Euler e("adjacencymatrix2");

    // Euler e("adjacencymatrixnotodd");
    Euler e(file_matrix);

    e.printAdjacencyMatrix();


	cerr << "Ejecutando algoritmo greedy con matriz de adyacencia de heurística " << endl;

    t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
    //Ejecutamos algoritmo iterativo
    e.fleuryAlgorithm();
    tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
    unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    cerr << "\tTiempo de ejec. (us): " << tejecucion <<endl;

    // Guardamos tam. de caso y t_ejecucion a fichero de salida
    fsalida<<" matriz adyacencia "<<tejecucion<<"\n";

    e.printEulerPath();
}