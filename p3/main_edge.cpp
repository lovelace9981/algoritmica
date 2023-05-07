#include "euler2.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 2){
        cerr << "Error: No se ha especificado el fichero que contiene el grafo" << endl;
        return 1;
    }
    euler2 e = euler2();
    

    // Leemos el fichero
    e.read(argv[1]);

    // Imprimimos el grafo
    cout << "GRAFO ANTES DE RESOLVERLO" << endl;
    e.print();
    cout << endl ;

    // Empezamos en el nodo 0
    e.solve();

    // Imprimimos el camino
    e.printSolution();
    cout << endl;

    return 0;
}
