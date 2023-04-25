#include "nodo.hpp"
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

    // Abrimos el fichero
    ifstream file;
    file.open(argv[1]);
    if(!file.is_open()){
        cerr << "Error: No se ha podido abrir el fichero" << endl;
        return 1;
    }
    // Leemos el número de nodos
    int numNodos;
    file >> numNodos;
    // Creamos el vector de nodos (grafo)
    vector<Nodo> grafo = vector<Nodo>(numNodos);
    for (int i = 0; i < numNodos; i++)
    {
        grafo[i].setNum(i);
        int numAristas;
        file >> numAristas;
        for (int j = 0; j < numAristas; j++)
        {
            int arista;
            file >> arista;
            grafo[i].addArista(arista);
        }
    }

    // Imprimimos el grafo
    for(auto nodo : grafo){
        cout << nodo.toString() ;
    }

    // Lista para ir guardando el camino que se toma
    list<int> camino;

    // Empezamos en el nodo 0
    int nodoActual = 0;
    while (grafo[nodoActual].getAristas() != 0) {
        int nodoSiguiente = grafo[nodoActual].getArista(0);
        // Comprobamos de todos los nodos adyacentes cuál es el que tiene más aristas
        for (int i=1; i<grafo[nodoActual].getAristas(); i++){
            if (grafo[grafo[nodoActual].getArista(i)].getAristas() > grafo[nodoSiguiente].getAristas()){
                nodoSiguiente = grafo[nodoActual].getArista(i);
            }
        }
        cout << "Nodo actual: " << nodoActual << " Aristas: " << grafo[nodoActual].getAristas() << endl;
        
        // Añadimos el nodo actual al camino
        camino.push_back(nodoActual);
        // Eliminamos la arista del nodo actual y del nodo siguiente
        grafo[nodoActual].deleteArista(nodoSiguiente);
        grafo[nodoSiguiente].deleteArista(nodoActual);
        // Actualizamos el nodo actual
        nodoActual = nodoSiguiente;
        cout << "Nodo siguiente: " << nodoActual << " Aristas: " << grafo[nodoActual].getAristas() << endl;
    }
    // Añadimos el último nodo al camino
    camino.push_back(nodoActual);

    // Imprimimos el camino
    for(auto nodo : camino){
        cout << nodo << " ";
    }
    cout << endl;

    // Imprimimos el grafo
    for(auto nodo : grafo){
        cout << nodo.toString() ;
    }

    return 0;
}
