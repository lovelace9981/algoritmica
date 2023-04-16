#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class DCD {
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

            
        // He puesto menor que, porque es posible que termine antes si encuentra un numbero muy pequeño
        // Pero eso no evita problemas como el 0,9
        bool primera_condicion(const vector<T> i, const vector<T>& j){
            for (int k = 0; k < K_DIMENSION; ++k){
                if (i[k] < j[k]){
                    return false;
                }
            }
            // Es >=
            return true;
        }

            
        bool segunda_condicion (const vector<T> i, const vector<T>& j){
            for (int k = 0; k < K_DIMENSION; ++k){
                if (i[k] > j[k]){
                    return true;
                }
            }
            return false;
        }

        bool domina (const vector<T>& i, const vector<T>& j){
            return primera_condicion(i,j) && segunda_condicion(i,j);
        }

        /**
          * Quitamos los puntos que sean dominados en esta "MITAD"
          */
        vector<vector<T>> prune_points(vector<vector<T>> & points){
            // El elemento es no dominado, hasta que encontremos a alguno que lo domine
            bool no_dominado = true;
            vector<vector<T>> point_no_dominados;
            // Metemos el primer elemento en no dominados
            point_no_dominados.push_back(points[0]);
            // Iteradores
            typename vector<vector<T>>::iterator it_componentes = points.begin() + 1;
            typename vector<vector<T>>::iterator it_no_dominados = point_no_dominados.begin();
            // Comprobamos todos los elementos con el array de no dominados,
            // si encontramos que el elemento siendo comparado domina a alguno que está ya en los no dominados,
            // sacamos de no dominados ese elemento y metemos el nuevo
            // Si el elemento siendo comparado es dominado por algún no dominado, hacemos un break
            while(it_componentes != points.end()){
                no_dominado = true;
                // Refrescamos el iterador - CAUSA Del seg fault ya que el iterador anterior estaba fuera de rango.
                it_no_dominados = point_no_dominados.begin();

                while(it_no_dominados != point_no_dominados.end()){
                    // Comprobamos si el elemento que estamos comparando domina al supuesto no dominado
                    // En este caso el comparado domina al no dominado.
                    if (domina((*it_componentes), (*it_no_dominados))) {
                        it_no_dominados = point_no_dominados.erase(it_no_dominados);
                    }
                    // Comprobamos si el elemento que estamos comparando es dominado por el supuesto no dominado
                    // En este caso el no dominado domina al comparado.
                    else if (domina((*it_no_dominados), (*it_componentes))){
                        no_dominado = false;
                        ++it_no_dominados;
                    }
                    // En este caso ninguno de los dos domina al otro, por lo que continuamos sin má.
                    else{
                        ++it_no_dominados;
                    }
                }
                
                // Insertamos nuevo no dominado.
                if (no_dominado){
                    point_no_dominados.push_back(*it_componentes);
                }

                // Incrementamos iterador de los componentes
                ++it_componentes;
            }

            #ifdef DEBUG_PARAMS_ALGORITHM
                for (int d = 0; d < point_no_dominados.size(); d++){
                    cout << "Componente *DEBUG_PARAMS_ALGORITHM* " << d << endl;
                    for (int dj = 0; dj < point_no_dominados[d].size(); dj++){
                            cout << point_no_dominados[d][dj] << " ";
                        }
                    }

                    cout << endl;
            #endif

            return point_no_dominados;
        }



    public:
        DCD(const int k, const int n): K_DIMENSION(k), N_COMPONENTES(n), MAX_NUMBER(10){
            vector<vector<T>> matrix {
                {1,2,3}, {2,3,4}, {10,5,3},
                {3,7,0}, {0,0,0}, {1,6,7},
                {5,6,3}, {8,3,1}, {1,3,5}};

            componentes=matrix;
        }

        /*
         * k - DIMENSION DE LOS PUNTOS
         * n - tamanio del problema
         * max_number - numero maximo de la semilla de SRAND, que empieza desde 0.
         */
        DCD(const int k, const int n, const int max_number): K_DIMENSION(k), N_COMPONENTES(n), MAX_NUMBER(max_number){
            gen_numbers();
        }

        ~DCD(){
            componentes.clear();
        }

        vector<vector<T>> divandconqDCD(vector<vector<T>> & puntos){
            // CASO BASE
            if (puntos.size() == 1){
                return puntos;
            }
                
            // SUBPROBLEMAS DIVISION DE LOS COMPONENTES POR LA MITAD
            // PRIMERA MITAD
            typename vector<vector<T>>::iterator start_half_1 = puntos.begin();
            typename vector<vector<T>>::iterator end_half_1 = (puntos.begin() + (puntos.size() / 2));
            // SEGUNDA MITAD - RECORDAR QUE LOS ITERADORES NO COPIAN LOS END, INTERVALO ABIERTO [0, MITAD), [MITAD, END)
            typename vector<vector<T>>::iterator start_half_2 = end_half_1;
            typename vector<vector<T>>::iterator end_half_2 = puntos.end();
            // COPIYING ELEMENTS
            vector<vector<T>> left(start_half_1, end_half_1);
            vector<vector<T>> right(start_half_2, end_half_2);
            // RECURSIVE CALL
            left = divandconqDCD(left);
            right = divandconqDCD(right);
            // MERGE RESULTS on LEFT
            left.insert(left.end(), right.begin(), right.end());\
            right.clear(); // LIBERAMOS MEMORIA
            // AL HACER EL MERGE EVALUAMOS DE NUEVO LOS SUBPROBLEMAS UNIDOS Y RETORNAMOS LOS NO_DOMINADOS MEZCLADOS
            return prune_points(left);
        }

        void divandconqCall(){
            no_dominados = divandconqDCD(componentes);
        }

        /**
         * @brief Method for printing the problem and the result
         * @pre Requires preexecution of gen_non_dominated
         */
        void print_problem() {
            if (no_dominados.size() == 0){
                cerr << "No se ha ejecutado el método gen_non_dominated " << endl;
            }
            else{
                cout << "All problem: " << endl;
                for (int i = 0; i < componentes.size(); i++){
                    cout << "Componente: " << " ";
                    for (int j = 0; j < K_DIMENSION; j++){
                        cout << " " << componentes[i][j] << " ";
                    }
                    cout << endl;
                }

                cout << "No dominados: " << endl;
                for (int i = 0; i < no_dominados.size(); i++){
                    cout << "Componente: " << " ";
                    for (int j = 0; j < K_DIMENSION; j++){
                        cout << " " << no_dominados[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        }
};