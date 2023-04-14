#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>


using namespace std;

/**
 * Clase que nos da los numeros no dominados en un plano de dimensión K
 * PREORDENAR
*/
template <class T>
class P2 {
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
            srand(time(NULL));
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

        void merge(const int left, const int medio, const int right) {
            // Iteradores, no coge el final, es un rango [left, medio), [medio, right)
            vector<int>::const_iterator begin_array1 = componentes.begin() + left;
            vector<int>::const_iterator end_array1_begin_array2 = componentes.begin() + medio;
            vector<int>::const_iterator end_array2 = componentes.begin() + right;
            // Creamos los arrays
            vector<int> array1(begin_array1, end_array1_begin_array2);
            vector<int> array2(end_array1_begin_array2, end_array2);

            // Averiguamos los tamanios de los subarrays
            int sizeofarray1 = array1.size();
            int sizeofarray2 = array2.size();

            // Empezamos a mezclar
            int i = 0;
            int j = 0;
            // K es el principio del array desordenado con DyQ
            int k = left;

            // Recogemos los elementos mas pequenios entre los dos array hasta que uno de los iteradores i j termine.
            while (i < sizeofarray1 && j < sizeofarray2) {
                // Al usar los vectores comparamos lexicograficamente
                if (array1[i] <= array2[j]) {
                    componentes[k] = array1[i];
                    i++;
                }
                else {
                    componentes[k] = array2[j];
                    j++;
                }
                k++;
            }

            // Recogemos los elementos restantes, que son mas grandes
            while (i < sizeofarray1) {
                componentes[k] = array1[i];
                i++;
                k++;
            }

            while (j < sizeofarray2){
                componentes[k] = array2[j];
                j++;
                k++;
            }
        }

        /*
            Algoritmo de Ordenacion MergeSort. D&C
        */
        void mergeSort(const int left, const int right) {
            // punto medio
            // int medio = (left + (right - left)) / 2;
            int medio = (left+right) / 2;
            // 1 + (2 - 1) / 2 = 2 / 2 = 1  l == m

            /*
                Control de que no se puede dividir mas el array, se convierte en un caso base. Donde medio y left ya son el mismo elemento
            */
            if (medio == left){
                return;
            }

            if (left < right) {
                mergeSort(left, medio);
                mergeSort(medio , right);
                merge(left, medio, right);
            }
        }
    
    public:
        /*
        * k - Dimension de puntos de un plano
        * n - Numero de componentes que se espera a evaluar
        * max_number - numero más grande que se debe generar de manera aleatoria
        */
        P2(const int k, const int n, const int max_number){
            assert(k > 0);
            
            K_DIMENSION = k;
            N_COMPONENTES = n;
            MAX_NUMBER = max_number;

            gen_numbers();
            mergeSort()
        }
        
        ~P2(){
            componentes.clear();
            no_dominados.clear();
        }

        /**
         * Metodo iterativo de los puntos no dominados
         * vi[a] >= vj[a] para todo a, y además se cumple
         *   vi[a] > vj[a] para al menos un valor de a.
         * COMPLEXITY CUBIC
         */
        void puntos_no_dominados(){
            no_dominados.clear();
            for (int i = 0; i < N_COMPONENTES-1; i++){
                for (int j = i+1; j < N_COMPONENTES; j++){
                    // Comparamos cada punto con la primera condicion
                    if (componentes[i] >= componentes[j]){
                        // Comprobamos la segunda condicion
                        for (int a = 0; a < K_DIMENSION; a++){
                            if (componentes[i][a] > componentes[j][a]){
                                // UN PUNTO NO DOMINADO EN UNA COORDENADA
                                no_dominado = true;
                                break;
                            }
                        }
                    }
                    else {
                        // DOMINADO
                        no_dominado = false;
                        break;
                    }                    
                }
                
                if (no_dominado){
                        no_dominados.push_back(componentes[i]);
                        no_dominado = false;
                }
            }
        }
        // Version divide and conquer del algoritmo.
        // Se comenzaría con min=0 y max=size, y se va llamando a la función para la mitad derecha e izquierda
        // El caso base es en el que solamente hay un componente, el cual sería no dominado.
        // Después se comparan los no dominados de cada mitad.
        vector<vector<T>> no_dominados_recursive1 (int min, int max) {
            vector<vector<T>> no_dominados_left;
            vector<vector<T>> no_dominados_right;
            vector<vector<T>> componentes_comparar;
            vector<vector<T>> no_dominados_merge;

            if (min == max){
                return no_dominados_merge;
            }
            else {
                no_dominados_left = no_dominados_recursive1(min, max/2);
                no_dominados_right = no_dominados_recursive1(max/2+1, max);

                // Los no dominados de la izquierda pueden ser dominados por alguno de la derecha y viceversa.
                // Para todos los de la izquierda, hay que comprobar si es dominado por alguno.
                // Para todos los de la derecha, hay que comprobar si es dominado por alguno.
                // Primero comprobamos si los de la derecha son dominados, si no es dominado lo agregamos a el array no dominados derDef
                // Después, comprobamos los de la izquierda pero solo con los del vector de no dominados derDef (los no dominados reales
                // de la derecha). Si no es dominado por ninguno, se agrega a un no dominados izqDef
                // Después tendríamos que unir los dos vectores izqDef y derDef.

                // Se ha encontrado el caso base, se procede a buscar los no dominados iniciales comparados de dos en dos
                if (no_dominados_left.empty() && no_dominados_right.empty()){
                    for (int i = min; i < max-1; i++){
                        for (int j = i + 1; j < max; j++){
                            if (no_dominado(componentes[i], componentes[j])){
                                no_dominados_merge.push_back(componentes[i]);
                            }
                        }
                    }

                }
                else {
                    // CASO NO BASE COMPARAMOS LOS NO_DOMINADOS_LEFT NO_DOMINADOS_RIGHT
                    for (int i = 0; i < no_dominados_left.size(); i++){
                        componentes_comparar.push_back(no_dominados_left[i]);
                    }

                    no_dominados_left.clear();

                    for (int i = 0; i < no_dominados_right.size(); i++){
                        componentes_comparar.push_back(no_dominados_right[i]);
                    }

                    no_dominados_right.clear();

                    /*  Al hacerlo de esta manera, estamos volviendo a comparar todos los de la izquierda con ellos mismos
                        e igualmente con los de la derecha, lo cual es menos eficaz.
                     */ 

                    for (int i = min; i < max-1; i++){
                        for (int j = i + 1; j < max; j++){
                            if (no_dominado(componentes_comparar[i], componentes_comparar[j])){
                                no_dominados_merge.push_back(componentes_comparar[i]);
                            }
                        }
                    }

                }

                return no_dominados_merge;
            }
        }
};


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