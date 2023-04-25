#include <set>
#include <string>
using namespace std;

class Nodo
{
private:
    set<int> aristas; // Lista de aristas
    int num; // Identificador del nodo
public:
    Nodo();
    Nodo(int num);
    ~Nodo();
    // Getters
    int getAristas() const;
    int getNum() const;
    int getArista(int i) const;
    // Setters
    void setNum(int num);
    void addArista(int arista);
    void deleteArista(int arista);
    string toString() const;
};
