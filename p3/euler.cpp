#include "euler.hpp"
// #define DEBUGEULER
/**
 * Para cumplir que tenga un camino de Euler, debemos tener en cuenta que:
 * Siempre hay 2 vertices con grado impar.  
 * El resto de los vertices tiene grado par.
*/
void Euler::evalIfEulerPath(){
    int odd = 0;
    
    for (int i = 0; i < nodes; i++){
        if (degreeEulerVertex[i] % 2 != 0){ //  odd vertex
            oddEulerVertex.push_back(i);
            odd++;
        }
    }
    
    #ifdef DEBUGEULER
    cout << "DEGREE VERTEX DEBUG" << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i<degreeEulerVertex.size(); i++){
        cout << degreeEulerVertex[i] << " ";
    }
    cout << endl;
    cout << "---------------------------------" << endl;
    #endif

    if (odd == 0){
        // cerr << "The graph have 0 odd vertex" << endl;
        // terminate();
        // Escogemos cualquier punto
        oddEulerVertex.push_back(0);
        srand(time(NULL)); // Semilla
        oddEulerVertex.push_back(rand()%nodes);
    }
    else if (odd == 1){
        cerr << "The graph have only one odd vertex" << endl;
        terminate();
    }
    else if (odd > 2){
        cerr << "The graph have more than 2 odd vertex" << endl;
        terminate();
    }

}

void Euler::storeEulerDegree(const int vertex){
    int degree = 0;

    for (int i = 0; i < nodes; i++){
        if (adjacencymatrix[vertex][i]==1){
            degree++;
        }
    }

    degreeEulerVertex.push_back(degree);
}

void Euler::setRowAdjacencyMatrix(const string r){
    vector<int> v_r;
    char a;
    int n_t;

    for (int i = 0; i < r.size(); i++){
        if(r.at(i) != '\t' &&  r.at(i) != ' '){
            a = r.at(i);
            n_t = a - '0';
            v_r.push_back(n_t);
        }
    }

    adjacencymatrix.push_back(v_r);
    v_r.clear();
}


void Euler::openFile(const string filename){
    fstream file;

    try {
        file.open(filename, ios::in);
    } catch (ifstream::failure e){
        cerr << "Exception opening the file\n";
    } 

    bool header = false;
    bool header_nodes = false;
    bool matrixMode = false;
    bool graphMode = false;
    bool errHeader = false;
    string line;

    // Obtaining header
    getline(file, line);
    if (!header){
        if (line == "M"){
            matrixMode = true;
        }
        else if (line == "G"){
            graphMode = true;
        }
        else {           
            cerr << "Error en el header" << endl;
            terminate();
        }
        header = true;
    }

    getline(file, line);
    char n = line.at(0);
    if (!header_nodes){
        nodes = n - '0';

        if (nodes <= 0){
            cerr << "Incorrect number of nodes " << nodes << " must be pair" << endl;
            terminate();
        }
        header_nodes = true;
    }  


    /**
      *  Obtaining lines of the matrix or the graphMode
      */
    int vertex = 0;
    while(getline(file, line)){
        if (header && header_nodes){
            if (matrixMode){
                setRowAdjacencyMatrix(line);
                storeEulerDegree(vertex);
            }
            else if (graphMode){
                // TO BE IMPLEMENTED
            }

            vertex++;
        }
    }
    /**
     * getting the odd vertex and eval if Euler Path
    */
    evalIfEulerPath();

}

void Euler::printAdjacencyMatrix(){
    cout << "ADJACENCY MATRIX " << endl;
    cout << "Nodes " << nodes << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i<adjacencymatrix.size(); i++){
        for (int j = 0; j<adjacencymatrix[i].size();j++)
            cout << adjacencymatrix[i][j] << " ";
        
        cout << endl;
    }
    cout << "DEGREE VERTEX" << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i<degreeEulerVertex.size(); i++){
        cout << degreeEulerVertex[i] << " ";
    }
    cout << endl;
    cout << "---------------------------------" << endl;

    cout << "OOD VERTEX" << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i<oddEulerVertex.size(); i++){
        cout << oddEulerVertex[i] << " ";
    }
    cout << endl;
    cout << "---------------------------------" << endl;

}

void Euler::printEulerPath(){
  for (int o = 0; o < oddEulerVertex.size(); o++){
        cout << "Path N: " << o << endl;
        cout << "---------------------------------" << endl;
        for (int i = 0; i < eulerPath[o].size(); i++){
            if(i != eulerPath[o].size()-1){
                cout << eulerPath[o][i] << " => ";
            }
            else {
                cout << eulerPath[o][i] << endl;
            }
            
        }
        cout << "---------------------------------" << endl;
  }
}


void Euler::fleuryAlgorithm(){
    vector<vector<int>> tempadjacency;

    for (int i = 0; i < nodes; i++){
        tempadjacency.push_back(adjacencymatrix[i]);
    }

    vector<int> tempdegreeEulerVertex = degreeEulerVertex;
    vector<int> actualEulerPath;
    
    int actualVertex = 0;
    int finalVertex = 0;
    int nextVertex = 0;
    // For take a vertex if all are dead end
    int firstVertexDeadEnd = -1; 
    int vertexWithNextDeadEnd = -1;

    bool end = false;
    bool next_not_dead_end = false;

    // La matriz de adyacencia es el mismo
    if (nodes == 1){
        actualEulerPath.push_back(0);
        eulerPath.push_back(actualEulerPath);
        actualEulerPath.clear();
    }
    else{
        for (int v = 0; v < oddEulerVertex.size(); v++){
            actualVertex = oddEulerVertex[v]; // Adquire the first odd vertex to start the eulerPath
            finalVertex = oddEulerVertex[v+1%degreeEulerVertex.size()]; // Adquire the final odd vertex off the eulerPath
            actualEulerPath.push_back(actualVertex); // Insert into vector the initial vertex
            // Greedy, from actual vertex, search the next vertex with adyacency and insert into the path
            // After insert into the path, clear the two 1 of adjacency matrix, that 1 means a edge
            while(!end){
                if (tempdegreeEulerVertex[actualVertex] > 0){
                    // Search vertex not dead end
                    while (nextVertex < nodes){
                        // Dead end
                        if (tempadjacency[actualVertex][nextVertex] == 1 && tempdegreeEulerVertex[nextVertex] == 1 && firstVertexDeadEnd == -1){
                                firstVertexDeadEnd = nextVertex; // Adquire the first vertex if all are dead end
                        }
                        else if (tempadjacency[actualVertex][nextVertex] == 1 && tempdegreeEulerVertex[nextVertex] > 1){
                            // Check if this vertex don't drive to a dead end
                            if (tempdegreeEulerVertex[nextVertex] == 2){
                                for (int i = 0; i < nodes; i++){
                                   if (i != actualVertex && tempadjacency[nextVertex][i] == 1 && tempdegreeEulerVertex[i] == 1 && vertexWithNextDeadEnd == -1){
                                        // Posible nextDeadEnd, because degree are 1, and this are vertex with one paths
                                        vertexWithNextDeadEnd = nextVertex;
                                   }
                                   else if (i != actualVertex && tempadjacency[nextVertex][i] == 1 && tempdegreeEulerVertex[i] > 1){
                                        next_not_dead_end = true; // Condicion de salida para el bucle grande
                                        // Encontramos que hay un siguiente camino multiple este vertex vale
                                        break;
                                   }
                                }
                            }
                            else if (tempdegreeEulerVertex[nextVertex] > 2){
                                break;
                            }

                            // // Break if not a next dead end
                            if (next_not_dead_end){
                                next_not_dead_end = false;
                                break;
                            }
                        } // Not dead end

                        // Last Vertex and eval if have dead end
                        if (nextVertex == nodes - 1){
                            if (vertexWithNextDeadEnd != -1){
                                nextVertex = vertexWithNextDeadEnd;
                            }
                            else if (firstVertexDeadEnd != -1){
                                nextVertex = firstVertexDeadEnd;
                            }
                            break;
                        }
                        
                        nextVertex++;
                    }

                    if (tempadjacency[actualVertex][nextVertex] == 1){
                        #ifdef DEBUGEULER
                        cout << "A" << actualVertex << endl;
                        cout << "N" << nextVertex << endl;
                        cout << "ADJACENCY MATRIX " << endl;
                        cout << "---------------------------------" << endl;
                        for (int i = 0; i<tempadjacency.size(); i++){
                            for (int j = 0; j<tempadjacency[i].size();j++)
                                cout << tempadjacency[i][j] << " ";
                            
                            cout << endl;
                        }
                        #endif

                        // Delete the adjacency points
                        tempadjacency[nextVertex][actualVertex] = 0;
                        tempadjacency[actualVertex][nextVertex] = 0;

                        #ifdef DEBUGEULER
                        cout << "NEW ADJACENCY MATRIX " << endl;
                        cout << "---------------------------------" << endl;
                        for (int i = 0; i<tempadjacency.size(); i++){
                            for (int j = 0; j<tempadjacency[i].size();j++)
                                cout << tempadjacency[i][j] << " ";
                            
                            cout << endl;
                        }
                        #endif

                        // Reducimos el grado
                        tempdegreeEulerVertex[actualVertex]--;
                        tempdegreeEulerVertex[nextVertex]--;

                        #ifdef DEBUGEULER
                        cout << "NEW DEGREE VECTOR" << endl;
                        cout << "---------------------------------" << endl;
                        for (int i = 0; i<tempdegreeEulerVertex.size(); i++){
                            cout << tempdegreeEulerVertex[i] << " ";
                        }
                        cout << endl;
                        #endif

                        actualVertex = nextVertex;
                        nextVertex = 0;
                        firstVertexDeadEnd = -1;
                        vertexWithNextDeadEnd = -1;

                        actualEulerPath.push_back(actualVertex);
                    }                    
                }
                else {
                    // Como el grafo es un camino donde los vertices se visitan una unica vez, cuando uno de los actuales termine por quedarse sin grado, es que ha terminad
                    // la busqueda
                    end = true;
                }
            }

            #ifdef DEBUG_EULER
            cout << "finalVertex " << finalVertex << endl;
            cout << "lastVertex path " << actualEulerPath[actualEulerPath.size()-1] << endl;
            cout << "**************************" << endl;
            cout << "PATH " << endl;
            cout << "**************************" << endl;

            for (int i = 0; i < actualEulerPath.size(); i++){
                if(i != actualEulerPath.size()-1){
                    cout << actualEulerPath[i] << " => ";
                }
                else {
                    cout << actualEulerPath[i] << endl;
                }
            }
            cout << "**************************" << endl;
            #endif

            // Insert the actualEulerPath for this odd
            eulerPath.push_back(actualEulerPath);

            // RESET for next odd
            actualEulerPath.clear();
            tempadjacency.clear();
            tempdegreeEulerVertex.clear();
            end = false;

            for (int i = 0; i < nodes; i++){
                tempadjacency.push_back(adjacencymatrix[i]);
            }   
            tempdegreeEulerVertex = degreeEulerVertex;
        }
    }
}

Euler::Euler(const string file){
    openFile(file);
}

Euler::~Euler(){
    adjacencymatrix.clear();
    eulerPath.clear();
}

