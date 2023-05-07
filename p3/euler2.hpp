#include <vector>
#include <list>
#include "nodo.hpp"
#include <fstream>
#include <iostream>
class euler2
{
private:
    vector<Nodo> grafo;
    list<int> camino;

public:
    euler2();
    ~euler2();
    void print();
    void printSolution();
    void read(string filename);
    void solve();
};
