#include <list>
using namespace std;
class Nodo
{
private:
    list<int> aristas; // Lista de aristas
public:
    Nodo(int numAristas);
    ~Nodo();
    int getAristas();
    void deleteArista(int arista);
};
