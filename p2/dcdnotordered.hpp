#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class DCD
{
private:
    list<vector<T>> componentes;
    list<vector<T>> no_dominados;

    const int K_DIMENSION;
    const int N_COMPONENTES;
    const int MAX_NUMBER;
    const int MIN_NUMBER = 0;

    /**
     *  Generador de puntos aleatorio.
     *  Usa los atributos internos para generar los puntos
     */
    void gen_numbers()
    {
        // INIT RAND
        srand(time(NULL));
        vector<T> componente_actual;
        T actual_rand_number;

        for (int i = 0; i < N_COMPONENTES; i++)
        {
            for (int j = 0; j < K_DIMENSION; j++)
            {
                actual_rand_number = MIN_NUMBER + (rand() % (MAX_NUMBER - MIN_NUMBER + 1));
                componente_actual.push_back(actual_rand_number);
            }

#ifdef DEBUG_PARAMS_GENERATOR
            cout << "Componente *DEBUG_PARAMS_GENERATOR* " << i << endl;
            for (int d = 0; d < K_DIMENSION; d++)
            {
                cout << componente_actual[i] << " ";
            }

            cout << endl;
#endif
            componentes.push_back(componente_actual);
            componente_actual.clear();
        }
    }

    // He puesto menor que, porque es posible que termine antes si encuentra un numbero muy pequeño
    // Pero eso no evita problemas como el 0,9
    bool primera_condicion(const vector<T> i, const vector<T> &j)
    {
        for (int k = 0; k < K_DIMENSION; ++k)
        {
            if (i[k] < j[k])
            {
                return false;
            }
        }
        // Es >=
        return true;
    }

    bool segunda_condicion(const vector<T> i, const vector<T> &j)
    {
        for (int k = 0; k < K_DIMENSION; ++k)
        {
            if (i[k] > j[k])
            {
                return true;
            }
        }
        return false;
    }

    bool domina(const vector<T> &i, const vector<T> &j)
    {
        return primera_condicion(i, j) && segunda_condicion(i, j);
    }

    void combinar(list<vector<T>>& conjunto1, list<vector<T>>& conjunto2)
    {
        bool no_dominado = false;


        // Comparamos todos los de conjunto2 con los de el conjunto1
        for (auto const &punto : conjunto2)
        {
            no_dominado = true;
            typename list<vector<T>>::iterator it = conjunto1.begin();
            while (it != conjunto1.end())
            {
                if (domina(punto, *it))
                {
                    // El punto del conjunto 2 domina al del conjunto 1, lo borramos y continuamos para comprobar si domina a otro o es dominado
                    it = conjunto1.erase(it);
                }
                else if (domina(*it, punto))
                {
                    // El punto de conjunto1 domina al de conjunto2, no lo añadimos y salimos del bucle
                    no_dominado = false;
                    it++;
                }
                else
                {
                    ++it;
                }
            }
            // Si es false, es que el punto es dominado.
            
            if (no_dominado)
                conjunto1.push_back(punto);
        }
    }

 
// #ifdef DEBUG_PARAMS_ALGORITHM>
//         for (int d = 0; d < point_no_dominados.size(); d++)
//         {
//             cout << "Componente *DEBUG_PARAMS_ALGORITHM* " << d << endl;
//             for (int dj = 0; dj < point_no_dominados[d].size(); dj++)
//             {
//                 cout << point_no_dominados[d][dj] << " ";
//             }
//         }

//         cout << endl;
// #endif

public:
    DCD(const int k, const int n) : K_DIMENSION(k), N_COMPONENTES(n), MAX_NUMBER(10)
    {
        list<vector<T>> matrix{
            {1, 2, 3}, {2, 3, 4}, {10, 5, 3}, {3, 7, 0}, {0, 0, 0}, {1, 6, 7}, {5, 6, 3}, {8, 3, 1}, {1, 3, 5}};

        componentes = matrix;
    }

    /*
     * k - DIMENSION DE LOS PUNTOS
     * n - tamanio del problema
     * max_number - numero maximo de la semilla de SRAND, que empieza desde 0.
     */
    DCD(const int k, const int n, const int max_number) : K_DIMENSION(k), N_COMPONENTES(n), MAX_NUMBER(max_number)
    {
        gen_numbers();
    }

    ~DCD()
    {
        componentes.clear();
    }

    list<vector<T>> divandconqDCD(typename list<vector<T>>::iterator start, typename list<vector<T>>::iterator end)
    {
        // CASO BASE
        int size = distance(start,end);

        if (size == 1)
        {
            return list<vector<int>>(start, end);
        }
        // SUBPROBLEMAS DIVISION DE LOS COMPONENTES POR LA MITAD
        //  MITAD
        typename list<vector<T>>::iterator mid = start;
        advance(mid, size/2);

        // RECURSIVE CALL
        list<vector<T>> left = divandconqDCD(start, mid);
        list<vector<T>> right = divandconqDCD(mid, end);
        
        // MERGE RESULTS ON LEFT
        combinar(left, right);
        // LEFT HAVE RESULTS
        return left ;
    }

    void divandconqCall()
    {
        no_dominados = divandconqDCD(componentes.begin(), componentes.end());
    }

    /**
     * @brief Method for printing the problem and the result
     * @pre Requires preexecution of gen_non_dominated
     */
    void print_problem(){
        if (no_dominados.size() == 0)
        {
            cerr << "No se ha ejecutado el método gen_non_dominated " << endl;
        }
        else
        {
            cout << "All problem: " << endl;
            for (auto &componente : componentes)
            {
                cout << "Componente: "
                     << " ";
                for (int j = 0; j < K_DIMENSION; j++)
                {
                    cout << " " << componente[j] << " ";
                }
                cout << endl;
            }

            cout << "No dominados: " << endl;
            for (auto &no_dominado : no_dominados)
            {
                cout << "Componente: " << " ";
                for (int j = 0; j < K_DIMENSION; j++)
                {
                    cout << " " << no_dominado[j] << " ";
                }
                cout << endl;
            }
        }
    }
};