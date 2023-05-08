#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <exception>
// RANDOM
#include <cstdlib>

using namespace std;

class Euler {
    private:
        vector<vector<int>> adjacencymatrix;
        vector<vector<int>> eulerPath;
        vector<int> degreeEulerVertex;
        vector<int> oddEulerVertex;
        
        int nodes;

        void evalIfEulerPath();
        void storeEulerDegree(const int vertex);
        void setRowAdjacencyMatrix(const string r);
        void openFile(const string file);
    public:
        Euler(const string file);
        ~Euler();
        
        void fleuryAlgorithm();
        void printEulerPath();
        void printAdjacencyMatrix();
};
