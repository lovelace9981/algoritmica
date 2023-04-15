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
class DCDORDERED {
    private:
        set<vector<T>> componentes;
        set<vector<T>> no_dominados;
        static int K_DIMENSION;
        static int N_COMPONENTES;
        static int MAX_NUMBER;
        const int MIN_NUMBER = 0;

        /**
          *  Generador de puntos aleatorio.
          *  Usa los atributos internos para generar los puntos
          */
        void gen_numbers(){
            // INIT RAND
            srand(time(NULL));
            vector<T> componente_actual;
            T actual_rand_number;

            for (int i = 0; i < N_COMPONENTES; i++){
                for (int j = 0; j < K_DIMENSION; j++){
                    actual_rand_number = MIN_NUMBER + (rand() % (MAX_NUMBER - MIN_NUMBER + 1 ));
                    componente_actual.push_back(actual_rand_number);
                }

                componentes.insert(componente_actual);
                componente_actual.clear();
            }
        }

        /**
          * Creamos el merge del subrpoblema, uniendo los subproblemas y ordenando los elementos restantes.
          * 
          */
        void merge(const int left, const int medio, const int right) {
            // Iteradores, no coge el final, es un rango [left, medio), [medio, right)
            vector<vector<T>>::const_iterator begin_array1 = componentes.begin() + left;
            vector<vector<T>>::const_iterator end_array1_begin_array2 = componentes.begin() + medio;
            vector<vector<T>>::const_iterator end_array2 = componentes.begin() + right;
            // Creamos los arrays
            vector<vector<T>> array1(begin_array1, end_array1_begin_array2);
            vector<vector<T>> array2(end_array1_begin_array2, end_array2);

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

        /**
          * Divide and conquer mergeSort. 
          * Problema principal: Encontrar los puntos menores en K dimension
          * Divisón en subproblemas: Se divide el conjunto de componentes en la mitad del tamaño total max.
          * Caso base: Se encuentra un subproblema que es el mismo punto, retornando un vector vacío.
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
        /**
          * k - Dimension de puntos de un plano
          * n - Numero de componentes que se espera a evaluar
          * max_number - numero más grande que se debe generar de manera aleatoria
          * Se preordena por todo K dimensión
          */
        DCDORDERED(const int k, const int n, const int max_number){
            assert(k > 0);
            
            K_DIMENSION = k;
            N_COMPONENTES = n;
            MAX_NUMBER = max_number;

            gen_numbers();
            mergeSort(0, N_COMPONENTES);
        }
        
        /**
          *
          *  
          */
        ~DCDORDERED(){
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

        /**
          * Divide and conquer preordenado. 
          * Problema principal: Encontrar los puntos no dominados en una dimensión K.
          * Precondición: Preordenar conjunto de componentes de puntos.
          * Divisón en subproblemas: Se divide el conjunto de componentes en la mitad del tamaño total max.
          * Caso base: Se encuentra un subproblema que es el mismo punto, retornando un vector vacío.
          */
        vector<vector<T>> no_dominados_recursive (int min, int max) {
            vector<vector<T>> no_dominados_left;
            vector<vector<T>> no_dominados_right;
            vector<vector<T>> componentes_comparar;
            vector<vector<T>> no_dominados_merge;

            if (min == max){
                return no_dominados_merge;
            }
            else {
                no_dominados_left = no_dominados_recursive(min, max/2);
                no_dominados_right = no_dominados_recursive(max/2+1, max);

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

