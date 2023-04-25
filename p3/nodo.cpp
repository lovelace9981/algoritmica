#include "nodo.hpp"

Nodo::Nodo()
{
    aristas = list<int>();
    num = 0;
}

Nodo::Nodo(int numAristas, int num)
{
    aristas = list<int>(numAristas);
    this->num = num;
}

Nodo::~Nodo()
{
    aristas.clear();
}

// Getters
int Nodo::getAristas() const
{
    return aristas.size();
}
int Nodo::getNum() const
{
    return num;
}

// Setters
void Nodo::setNum(int num)
{
    this->num = num;
}
void Nodo::addArista(int arista)
{
    aristas.push_back(arista);
}

void Nodo::deleteArista(int arista)
{
    aristas.remove(arista);
}

string Nodo::toString() const
{
    string str = "Nodo " + to_string(num) + ":\n";
    for (list<int>::const_iterator it = aristas.begin(); it != aristas.end(); ++it)
    {
        str += "\t" + to_string(*it) + "\n";
    }
    return str;
}