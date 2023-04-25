#include "nodo.hpp"

Nodo::Nodo(int numAristas)
{
    aristas = list<int>(numAristas);
}

Nodo::~Nodo()
{
    aristas.clear();
}

int Nodo::getAristas()
{
    return aristas.size();
}

void Nodo::deleteArista(int arista)
{
    aristas.remove(arista);
}