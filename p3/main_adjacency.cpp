#include "euler.hpp"

int main(){
    // Euler e("adjacencymatrix");
    Euler e("adjacencymatrix2");

    // Euler e("adjacencymatrixnotodd");

    e.printAdjacencyMatrix();
    e.greedyEulerAdjacencyMatrix();
    e.printEulerPath();
}