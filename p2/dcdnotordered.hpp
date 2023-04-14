#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

template <class T>
class DCD {
    private: 
        vector<vector<T>> componentes;
        vector<vector<T>> no_dominados;
        static int K_DIMENSION;
        static int N_COMPONENTES;
        static int MAX_NUMBER;
        const int MIN_NUMBER = 0;

        // Metodo privado de generador.
        void gen_numbers(){
            // INIT RAND
            srand(TIME(NULL));
            vector<vector<T>> componente_actual;
            T actual_rand_number;

            for (int i = 0; i < N_COMPONENTES; i++){
                for (int j = 0; j < K_DIMENSION; j++){
                    actual_rand_number = MIN_NUMBER + (rand() % (MAX_NUMBER - MIN_NUMBER + 1 ));
                    componente_actual.push_back(actual_rand_number);
                }

                componentes.push_back(componente_actual);
                componente_actual.clear();
            }
            // FREEING MEMORY
            componente_actual.clear();
        }

            
        bool check_no_dominado(vector<T> & componente_A, vector<T> & componente_B){
            bool no_dominado = false;
            // Comparamos cada punto con la primera condicion
            if (componente_A >= componente_B){
                // Comprobamos la segunda condicion
                for (int a = 0; a < K_DIMENSION; a++){
                    if (componentes[i][a] > componentes[j][a]){
                        // UN PUNTO NO DOMINADO EN UNA COORDENADA
                        no_dominado = true;
                        break;
                    }
                }
            }

            return no_dominado;
        }

        /**
          * Quitamos los puntos que sean dominados en esta "MITAD"
          */
        vector<vector<T>> prune_points(vector<vector<T>> & points){
            bool no_dominado = false;
            vector<vector<T>> points_no_dominados;        

            for (int i = 0; i < points.size()-1; i++){
                for (int j = i + 1; j < points.size(); j++){
                    if(check_no_dominado(points[i], points[j])){
                        no_dominado = true;
                        break;
                    }
                }

                if (no_dominado){
                    points_no_dominados.push_back(points[i]);
                }
            }

            return points_no_dominados;
        }

    public:
        /*
         * k - DIMENSION DE LOS PUNTOS
         * n - tamanio del problema
         * max_number - numero maximo de la semilla de SRAND, que empieza desde 0.
         */
        DCD(const int k, const int n, const int max_number){
            K_DIMENSION = k;
            N_COMPONENTES = n;
            MAX_NUMBER = max_number;

            gen_numbers();
            no_dominados = divandconqDCD(this->componentes);
        }

        ~DCD(){
            componentes.clear();
            no_dominados.clear();
        }

        vector<vector<T>> divandconqDCD(vector<vector<T>> puntos){
            // CASO BASE
            if (componentes.size() == 0)
                return puntos;
            
            // SUBPROBLEMAS DIVISION DE LOS COMPONENTES POR LA MITAD
            // PRIMERA MITAD
            vector<vector<T>>::iterator start_half_1 = puntos.begin();
            vector<vector<T>>::iterator end_half_1 = (puntos.begin() + (puntos.size() / 2));
            // SEGUNDA MITAD - RECORDAR QUE LOS ITERADORES NO COPIAN LOS END, INTERVALO ABIERTO [0, MITAD), [MITAD, END)
            vector<vector<T>>::iterator start_half_2 = end_half_1;
            vector<vector<T>>::iterator end_half_2 = puntos.end();
            // COPING ELEMENTS
            vector<vector<T>> left(start_half_1, end_half_1);
            vector<vector<T>> right(start_half_2, end_half_2);
            // PRUNE
            left = prune_points(left);
            right = prune_points(right);
            // RECURSIVE CALL
            left = divandconqDCD(left);
            right = divandconqDCD(right);
            // MERGE RESULTS on LEFT
            left.insert(left.end(), right.begin(), right.end());
            right.clear(); // LIBERAMOS MEMORIA
            // AL HACER EL MERGE EVALUAMOS DE NUEVO LOS SUBPROBLEMAS UNIDOS Y RETORNAMOS LOS NO_DOMINADOS MEZCLADOS
            return prune_points(left);
        }
        
};