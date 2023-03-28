#include <iostream>
#include <vector>

using namespace std;

template <class T>
class P2 {
    private:
        vector<vector<T>> componentes;
        vector<int> no_dominados;
        static int K_DIMENSION;
        static int N_COMPONENTES;
        static int MAX_NUMBER;

        // Metodo privado de generador.

        // 
    public:
        P2(const int k, const int n, const int max_number){
            if (k > 0){
                K_DIMENSION = k;
            }
            
        }

};