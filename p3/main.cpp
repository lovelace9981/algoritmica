#include "nodo.hpp"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 2){
        cerr << "Error: No se ha especificado el fichero que contiene el grafo" << endl;
        return 1;
    }
    return 0;
}
