#include <vector>

using namespace std;

/*Algoritmos iterativos*/

/*
    Primer ejercicio: Dado un vector de N elementos repetidos, retornar otro, que no esté repetido.7
    Eficiencia teorica N^2
    OK
*/
void vectorSinRepeticion(const vector<int> &vectorOriginal, vector<int> &vectorFinal, const int N)
{
    // Booleano controlador de encontrar repetidos
    bool encontrado = false;
    int tamanioVector = vectorFinal.size();
    // Caso Base, aniadimos el primer elemento, ya que ese nunca va a estar repetido
    vectorFinal.push_back(vectorOriginal[0]);

    for (int i = 1; i < N; i++)
    {
        // Bucle de recorrido interno, para buscar el duplicado.
        for (int j = 0; j < tamanioVector && !encontrado; j++)
        {
            // Encontramos un duplicado, nos salimos del bucle.
            if (vectorFinal[j] == vectorOriginal[i])
            {
                encontrado = true;
            }
        }

        // Hemos encontrado un elemento en el vectorFinal, aniadimos el elemento del vectorOriginal
        if (!encontrado)
        {
            vectorFinal.push_back(vectorOriginal[i]);
            tamanioVector = vectorFinal.size();
        }
        else
        {
            encontrado = false;
        }
    }
}

void merge(vector<int> &unorderedVector, const int left, const int medio, const int right) {
    // Iteradores, no coge el final, es un rango [left, medio), [medio, right)
    vector<int>::const_iterator begin_array1 = unorderedVector.begin() + left;
    vector<int>::const_iterator end_array1_begin_array2 = unorderedVector.begin() + medio;
    vector<int>::const_iterator end_array2 = unorderedVector.begin() + right;
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
    while (i < sizeofarray1 && j < sizeofarray2)
    {
        if (array1[i] <= array2[j])
        {
            unorderedVector[k] = array1[i];
            i++;
        }
        else
        {
            unorderedVector[k] = array2[j];
            j++;
        }
        k++;
    }

    // Recogemos los elementos restantes, que son mas grandes
    while (i < sizeofarray1)
    {
        unorderedVector[k] = array1[i];
        i++;
        k++;
    }

    while (j < sizeofarray2)
    {
        unorderedVector[k] = array2[j];
        j++;
        k++;
    }
}

/*
    Algoritmo de Ordenacion MergeSort. D&C
*/
void mergeSort(vector<int> &unorderedVector, const int left, const int right) {
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
    mergeSort(unorderedVector, left, medio);
    mergeSort(unorderedVector, medio , right);
    merge(unorderedVector, left, medio, right);
    }
}

/*
    Ejercicio 2:
    El algoritmo de repetidos Eficiente con entrada ordenada
    // Ordenamos el vector previamente con el algoritmo mas eficiente posible debido a los elementos aleatorios generados.
    // mergeSort(vectorOriginal, 0, N);

*/
void repetidosEficienteOrdenado(vector<int> &vectorOriginal, vector<int> &vectorFinal, const int N)
{
    // Cogemos de los elementos ordenados, los que no se repitan mas de una vez
    int actual = -1;

    for (int i = 0; i < vectorOriginal.size(); i++)
    {
        if (actual != vectorOriginal[i])
        {
            actual = vectorOriginal[i];
            vectorFinal.push_back(actual);
        }
    }
}

template <class T>
class APO {
    private:
        vector<T> apo;

        void swap(T * l, T * r){
            T intercambio = *l;
            *l = *r;
            *r = intercambio;
        }

        /* 
            Reestructuracion del arbol
            N SIZE OF HEAP
            i node rooted of HEAP N
        */
        void heapify(int N, int i){
            int hijo_left = 2 * i + 1;
            int hijo_right = 2 * i + 2;
            int largest = i;

            // Comparamos si alguno de los hijos es el mas grande
            if (hijo_left < N && apo[hijo_left] > apo[largest]){
                largest = hijo_left;
            }

            if (hijo_right < N && apo[hijo_right] > apo[largest]){
                largest = hijo_right;
            }
            
            if (largest != i){
                swap(&apo[i], &apo[largest]);

                // Recursively heapify the affected
                // sub-tree
                heapify(N, largest);
            }
        }
        
    public:
        APO(const vector<T> & v){
            apo = v;

        }

        APO(){}

        ~APO(){
            if (apo.size() > 0){
                apo.clear();
            }
        }

        APO<T>& operator= (const vector<T> & v){
            this -> apo = v;
            return *this;
        }

        void HeapSort(){
            // Formamos el arbol
            for (int i = apo.size() / 2 - 1; i >= 0; i--){
                heapify(apo.size(), i);
            }

            // HeapSorting
            for (int i = apo.size() - 1; i >= 0; i--){
                swap(&apo[0],&apo[i]);
                heapify(i, 0);
            }
        }

        void printVectorOrdenado(){
            for (int i = 0; i < apo.size(); i++)
                cout << apo[i] << " ";
            cout << endl;
        }
    };