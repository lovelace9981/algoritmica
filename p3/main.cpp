#include "nodo.hpp"
#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main(int argc, char const *argv[])
{
    // if(argc < 2){
    //     cerr << "Error: No se ha especificado el fichero que contiene el grafo" << endl;
    //     return 1;
    // }
    // Creamos un grafo de ejemplo, conexo y que tiene un número par de aristas
    // Lista para ir guardando el camino que se toma
    list<int> camino;
    // Vector grafo
    vector<Nodo> grafo;
    grafo.push_back(Nodo(0));
    grafo.push_back(Nodo(1));
    grafo.push_back(Nodo(2));
    grafo.push_back(Nodo(3));
    grafo.push_back(Nodo(4));
    
    // Añadimos las aristas
    for (int i = 0; i < grafo.size(); i++)
    {
        grafo[i].addArista((i + 1) % grafo.size());
        grafo[i].addArista((i + 2) % grafo.size());
    }
    grafo[grafo.size() - 1].addArista(3);
    grafo[grafo.size() - 1].addArista(2);

    // Imprimimos el grafo
    for(auto nodo : grafo){
        cout << nodo.toString() ;
    }

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
        // Añadimos el nodo actual al camino
        camino.push_back(nodoActual);
        // Eliminamos la arista del nodo actual y del nodo siguiente
        grafo[nodoActual].deleteArista(nodoSiguiente);
        grafo[nodoSiguiente].deleteArista(nodoActual);
        // Actualizamos el nodo actual
        nodoActual = nodoSiguiente;
    }

    // Imprimimos el camino
    for(auto nodo : camino){
        cout << nodo << " ";
    }
    cout << endl;

    return 0;
}
