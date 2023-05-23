#include <vector>
#include <iostream>
using namespace std ;

int sumaArray(vector<int> array) {
    int suma = 0;
    for (int i = 0; i < array.size(); i++) {
        suma += array[i];
    }
    return suma;
}

int main(int argc, char const *argv[])
{
    int n, m, k;
    n = 20;
    m = 170;
    k = 80;
    vector<int> num = {n,m,k};
    vector<int> array = {0,0,0} ;
    int cont = 0 ;
    while (true) {
        cont ++ ;
        // Imprimimos la combinación
        for (int i = 0; i < array.size(); i++) {
            cout << array[i] << " ";
        }
        cout << endl;
        // Si no hay más combinaciones salimos del bucle
        if(array == num){
            break;
        }
        // Sumamos uno a la primera posición
        array[0] ++ ;

        if(array == num){
            break;
        }else{
            for(int i = 0; i < array.size(); i++){
                if(array[i] == num[i] and array[i+1] != num[i+1]){
                    array[i] = 0;
                    array[i+1] ++;
                }
            }
        }
    }
    cout << "Total: " << cont << endl;
    return 0;
}
