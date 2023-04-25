#include <list>
using namespace std;

class Nodo
{
private:
    list<int> aristas; // Lista de aristas
public:
    Nodo();
    Nodo(int numAristas);
    ~Nodo();
    int getAristas() const;
    void deleteArista(int arista);
};
