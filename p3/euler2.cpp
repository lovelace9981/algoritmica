#include "euler2.hpp"

euler2::euler2()
{
    grafo = vector<Nodo>();
    camino = list<int>();
}

euler2::~euler2()
{
    grafo.clear();
    camino.clear();
}

void euler2::print()
{
    for (auto nodo : grafo)
    {
        cout << nodo.toString();
    }
}

void euler2::printSolution()
{
    list<int>::iterator it = camino.begin();
    while (it!=camino.end())
    {
        if(next(it) != camino.end())
            cout << *it << " => ";
        else
            cout << *it ;
        it++;
    }
    cout << endl;
    cout << "---------------------------------" << endl;
}

void euler2::solve()
{
    int nodoActual = 0;
    while (grafo[nodoActual].getAristas() != 0)
    {
        int nodoSiguiente = grafo[nodoActual].getArista(0);
        // Comprobamos de todos los nodos adyacentes cuál es el que tiene más aristas
        for (int i = 1; i < grafo[nodoActual].getAristas(); i++)
        {
            if (grafo[grafo[nodoActual].getArista(i)].getAristas() > grafo[nodoSiguiente].getAristas())
            {
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
    // Añadimos el último nodo al camino
    camino.push_back(nodoActual);
}

void euler2::read(string filename)
{
    // Abrimos el fichero
    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cerr << "Error: No se ha podido abrir el fichero" << endl;
        throw "Error: No se ha podido abrir el fichero";
    }

    // Leemos la cabecera para comprobar que es un grafo
    string cabecera;
    file >> cabecera;
    if(cabecera != "G")
    {
        cerr << "Error: El fichero no contiene un grafo" << endl;
        throw "Error: El fichero no contiene un grafo";
    }

    // Leemos el número de nodos
    int numNodos;
    file >> numNodos;
    // Creamos el vector de nodos (grafo)
    grafo = vector<Nodo>(numNodos);
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
}

