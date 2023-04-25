#include "nodo.hpp"

Nodo::Nodo()
{
    aristas = set<int>();
    num = 0;
}

Nodo::Nodo(int num)
{
    aristas = set<int>();
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
int Nodo::getArista(int i) const
{
    set<int>::const_iterator it = aristas.begin();
    for (int j = 0; j < i; j++)
    {
        it++;
    }
    return *it;
}

// Setters
void Nodo::setNum(int num0)
{
    num = num0;
}
void Nodo::addArista(int arista)
{
    aristas.insert(arista);
}

void Nodo::deleteArista(int arista)
{
    aristas.erase(arista);
}

string Nodo::toString() const
{
    string str = "Nodo " + to_string(num) + ":\n";
    for (set<int>::const_iterator it = aristas.begin(); it != aristas.end(); ++it)
    {
        str += "\t" + to_string(*it) + "\n";
    }
    return str;
}