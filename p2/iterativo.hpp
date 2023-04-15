#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

// #define DEBUG_PARAMS_GENERATOR
// #define DEBUG_PARAMS_ALGORITHM
/**
 * Clase que nos da los numeros no dominados en un plano de dimensión K
 * PREORDENAR
 */
template <class T>
class non_dominated_iterative
{
private:
    vector<vector<T>> componentes;
    vector<vector<T>> no_dominados;
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

public:
    /**
     * k - Dimension de puntos de un plano
     * n - Numero de componentes que se espera a evaluar
     * max_number - numero más grande que se debe generar de manera aleatoria
     * Se preordena por todo K dimensión
     */
    non_dominated_iterative(const int k, const int n, const int max_number) : K_DIMENSION(k), N_COMPONENTES(n), MAX_NUMBER(max_number)
    {
        gen_numbers();
    }

    /**
     *
     *
     */
    ~non_dominated_iterative()
    {
        componentes.clear();
        no_dominados.clear();
    }

    /**
     * Metodo iterativo de los puntos no dominados
     * vi[a] >= vj[a] para todo a, y además se cumple
     *   vi[a] > vj[a] para al menos un valor de a.
     * COMPLEXITY CUBIC
     */
    void gen_non_dominated(){
        // El elemento es no dominado, hasta que encontremos a alguno que lo domine
        bool no_dominado = true;
        // El elemento domina alguno del vector de los no_dominados.
        bool domina = false;
        // Iteradores
        typename vector<vector<T>>::iterator it_componentes = componentes.begin() + 1;
        typename vector<vector<T>>::iterator it_no_dominados = no_dominados.begin();

        if (no_dominados.size() != 0)
            no_dominados.clear();
        
        
        // Metemos el primer elemento en no dominados
        no_dominados.push_back(componentes[0]);
        
        // Comprobamos todos los elementos con el array de no dominados,
        // si encontramos que el elemento siendo comparado domina a alguno que está ya en los no dominados,
        // sacamos de no dominados ese elemento y metemos el nuevo
        // Si el elemento siendo comparado es dominado por algún no dominado, hacemos un break
        while(it_componentes != componentes.end()){
            no_dominado = true;
            while(it_no_dominados != no_dominados.end()){
                // Comprobamos si el elemento que estamos comparando domina al supuesto no dominado
                // 1a Condicion: Se busca que sea mayor o igual en todas las coordenadas K.  
                if ((*it_componentes) >= (*it_no_dominados)){
                    for (int k = 0; k < K_DIMENSION; k++){
                        // 2a Condicion: Para convertirse en no dominado, debemos encontrar al menos un punto en la coordenada K en el que sea 
                        // mayor absoluto.
                        if ((*it_componentes)[k] > (*it_no_dominados)[k]){
                            domina = true;
                            break; // Salimos del K ya que hay al menos un elemento que no es dominado en el espacio K del componente actual.
                        }
                    }
                }
                
                // Comprobamos si el no dominado domina a el que estamos comparando
                if(no_dominado){
                    if ((*it_no_dominados) >= (*it_componentes)){
                        for (int k = 0; k < K_DIMENSION; k++){
                            if ((*it_no_dominados)[k] > (*it_componentes)[k]){
                                no_dominado = false;
                                break;
                            }
                        }
                    }
                }
                
                // Aquí se actualiza el iterador de los no dominados
                // Si el que estamos comparando domina al supuesto no dominado, lo eliminamos
                if (domina){
                    it_no_dominados = no_dominados.erase(it_no_dominados);
                    domina = false;
                }
                // Si no, tan solo avanzaremos para comprobar el siguiente "no dominado"
                else{
                    it_no_dominados++;
                }
            }
            
            if (no_dominado){
                no_dominados.push_back((*it_componentes));
            }

            // Incrementamos iterador de los componentes
            it_componentes++;
        }

        #ifdef DEBUG_PARAMS_ALGORITHM
            for (int d = 0; d < no_dominados.size(); d++){
                cout << "Componente *DEBUG_PARAMS_ALGORITHM* " << d << endl;
                for (int dj = 0; dj < no_dominados[d].size(); dj++){
                        cout << no_dominados[d][dj] << " ";
                    }
                }

                cout << endl;
        #endif
       
    }

    /**
     * @brief Method for printing the problem and the result
     * @pre Requires preexecution of gen_non_dominated
     */
    void print_problem()
    {
        if (no_dominados.size() == 0)
        {
            cerr << "No se ha ejecutado el método gen_non_dominated " << endl;
        }
        else
        {
            cout << "All problem: " << endl;
            for (int i = 0; i < componentes.size(); i++)
            {
                cout << "Componente: "
                     << " ";
                for (int j = 0; j < K_DIMENSION; j++)
                {
                    cout << " " << componentes[i][j] << " ";
                }
                cout << endl;
            }

            cout << "No dominados: " << endl;
            for (int i = 0; i < no_dominados.size(); i++)
            {
                cout << "Componente: "
                     << " ";
                for (int j = 0; j < K_DIMENSION; j++)
                {
                    cout << " " << no_dominados[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
};