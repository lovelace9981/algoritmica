#include "nodo.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 2){
        cerr << "Error: No se ha especificado el fichero que contiene el grafo" << endl;
        return 1;
    }
    int numNodos = atoi(argv[1]);
    vector<Nodo> grafo = vector<Nodo>(numNodos);
    for (int i = 0; i < numNodos; ++i)
    {
        grafo[i] = Nodo(0, i);
        grafo[i].addArista(i+1);
        grafo[i].addArista(i+3);
    }

    for(auto nodo : grafo){
        cout << nodo.toString() << endl;
    }
    
    return 0;
}
