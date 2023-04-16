#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

/**
 * Clase que nos da los numeros no dominados en un plano de dimensión K
 * PREORDENAR
 */
template <class T>
class DCDDIMENSION
{
private:
    set<vector<T>> componentes;
    set<vector<T>> no_dominados;
    int K_DIMENSION;
    int N_COMPONENTES;
    int MAX_NUMBER;
    int MIN_NUMBER = 0;

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

            componentes.insert(componente_actual);
            componente_actual.clear();
        }
    }

public:
    /**
     * k - Dimension de puntos de un plano
     * n - Numero de componentes que se espera a evaluar
     * max_number - numero más grande que se debe generar de manera aleatoria
     */
    DCDDIMENSION(const int k, const int n, const int max_number)
    {
        assert(k > 0);

        K_DIMENSION = k;
        N_COMPONENTES = n;
        MAX_NUMBER = max_number;

        gen_numbers();
    }

    DCDDIMENSION(const int k, const int n): K_DIMENSION(k), N_COMPONENTES(n), MAX_NUMBER(10){
            set<vector<T>> matrix {
                {1,2,3}, {2,3,4}, {10,5,3},
                {3,7,0}, {0,0,0}, {1,6,7},
                {5,6,3}, {8,3,1}, {1,3,5}};

            componentes=matrix;
        }

    /**
     *
     *
     */
    ~DCDDIMENSION()
    {
        componentes.clear();
        no_dominados.clear();
    }

    /**
     * Divide and conquer preordenado.
     * Problema principal: Encontrar los puntos no dominados en una dimensión K.
     * Precondición: Preordenar conjunto de componentes de puntos.
     * Divisón en subproblemas: Se divide el conjunto de componentes en la mitad del tamaño total max.
     * Caso base: Se encuentra un subproblema que es el mismo punto, retornando un vector vacío.
     */
    // set<vector<T>> no_dominados_recursive(set<vector<T>> entrada, int coordenada);
    // bool primera_condicion(const vector<T> i, const vector<T> &j);
    // bool segunda_condicion(const vector<T> i, const vector<T> &j);
    // bool domina(const vector<T> &i, const vector<T> &j);
    // set<vector<T>> combinar(set<vector<T>> conjunto1, set<vector<T>> conjunto2);

    // void puntos_no_dominados();
    // void print_problem();

    set<vector<T>> no_dominados_recursive(set<vector<T>> entrada, int coordenada)
    {
        // Calculamos la media de la coordenada
        double media = 0;
        for (auto const &punto : entrada)
            media += punto[coordenada];

        media /= entrada.size();

        // Dividimos el conjunto de puntos en dos conjuntos
        set<vector<T>> conjunto1, conjunto2;
        for (auto const &punto : entrada)
        {
            if (punto[coordenada] <= media)
                conjunto1.insert(punto);
            else
                conjunto2.insert(punto);
        }

        // Llamamos a la función recursiva para cada conjunto con una coordenada distinta
        if (conjunto1.size() > 1)
            conjunto1 = no_dominados_recursive(conjunto1, (coordenada + 1) % K_DIMENSION);
        if (conjunto2.size() > 1)
            conjunto2 = no_dominados_recursive(conjunto2, (coordenada + 1) % K_DIMENSION);

        set<vector<T>> resultado;
        // Combinamos los dos conjuntos en uno solo dejando solo los no dominados
        resultado = combinar(conjunto1, conjunto2);

        // Devolvemos la lista resultante
        return resultado;
    }

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

    set<vector<T>> combinar(set<vector<T>> conjunto1, set<vector<T>> conjunto2)
    {
        set<vector<T>> resultado;
        bool no_dominado = false;

        // Metemos en resultado el conjunto 1
        for (auto const &punto : conjunto1)
            resultado.insert(punto);

        // Comparamos todos los de conjunto2 con los de el resultado
        for (auto const &punto : conjunto2)
        {
            no_dominado = true;

            typename set<vector<T>>::iterator it = resultado.begin();
            while (it != resultado.end())
            {
                if (domina(punto, *it))
                {
                    // El punto domina al de resultado, lo borramos y continuamos para comprobar si domina a otro o es dominado
                    it = resultado.erase(it);
                }
                else if (domina(*it, punto))
                {
                    // El punto de resultado domina al de conjunto2, no lo añadimos y salimos del bucle
                    no_dominado = false;
                    it++ ;
                }
                else
                {
                    ++it;
                }
            }
            if(no_dominado)
                resultado.insert(punto);
        }

        return resultado;
    }

    void puntos_no_dominados()
    {
        no_dominados.clear();
        no_dominados = no_dominados_recursive(componentes, 0);
    }

    void print_problem()
    {
        // if (no_dominados.size() == 0)
        // {
        //     cerr << "No se ha ejecutado el método gen_non_dominated " << endl;
        // }
        // else
        // {
            cout << "All problem: " << endl;
            for (auto const &punto : componentes)
            {
                cout << "Componente: "
                     << " ";
                for (int j = 0; j < K_DIMENSION; j++)
                {
                    cout << " " << punto[j] << " ";
                }
                cout << endl;
            }

            cout << "No dominados: " << endl;
            for (auto const &punto : no_dominados)
            {
                cout << "Componente: "
                     << " ";
                for (int j = 0; j < K_DIMENSION; j++)
                {
                    cout << " " << punto[j] << " ";
                }
                cout << endl;
            }
        }
    // }
};
