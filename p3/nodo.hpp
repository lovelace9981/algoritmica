#include <list>
#include <string>
using namespace std;

class Nodo
{
private:
    list<int> aristas; // Lista de aristas
    int num; // Identificador del nodo
public:
    Nodo();
    Nodo(int numAristas, int num);
    ~Nodo();
    // Getters
    int getAristas() const;
    int getNum() const;
    // Setters
    void setNum(int num);
    void addArista(int arista);
    void deleteArista(int arista);
    string toString() const;
};
