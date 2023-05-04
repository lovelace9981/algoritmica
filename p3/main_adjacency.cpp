#include "euler.hpp"

int main(){
    // Euler e("adjacencymatrix");
    Euler e("adjacencymatrix2");

    e.printAdjacencyMatrix();
    e.greedyEulerAdjacencyMatrix();
    e.printEulerPath();
}