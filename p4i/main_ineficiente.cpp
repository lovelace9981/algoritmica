#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <cmath>

using namespace std;

struct Compra
{
    vector<int> acciones;
    float beneficio = 0;
    float coste = 0;

    Compra() {}
    Compra(vector<int> acciones, int beneficio) : acciones(acciones), beneficio(beneficio) {}
};

float calcularBeneficio (const vector<int>& acciones, const vector<float>& price, const vector<float>& profit)
{
    float beneficio = 0;
    for (int i = 0; i < acciones.size(); i++)
    {
        beneficio +=  price[acciones[i]] * profit[acciones[i]];
    }
    return beneficio;
}

float calcularCoste(const vector<int>& acciones, const vector<float>& price, const vector<float>& commissions)
{
    float coste = 0;
    for (int i = 0; i < acciones.size(); i++)
    {
        coste += price[acciones[i]] + commissions[acciones[i]];
    }
    return coste;
}

// Función que devuelve una compra
void printCombinations(float budget, const vector<int>& array, const vector<float>& price, const vector<float>& commissions , const vector<float>& profit)
{
    // Create a vector to store the combinations.
    set<vector<int>> combinations;

    cout << "Tenemos " << pow(2, array.size()) << " combinaciones posibles" << endl;

    // Iterate over all possible combinations.
    for (int i = 0; i < pow(2, array.size()); i++)
    {
        // Create a vector to store the current combination.
        vector<int> combination;

        // Iterate over the bits of i.
        for (int j = 0; j < array.size(); j++)
        {
            // If the jth bit of i is set, add the jth element of array to the combination.
            if (i & (1 << j))
            {
                combination.push_back(array[j]);
            }
        }

        // Si el coste de la combinación es menor que el presupuesto, la añadimos a la lista de combinaciones
        if (calcularCoste(combination, price, commissions) <= budget)
        {
            combinations.insert(combination);
        }


        // // If the combination has the desired size, add it to the list of combinations.
        // if (combination.size() == r)
        // {
        //     combinations.push_back(combination);
        // }
    }

    // Mejor compra posible
    Compra mejorCompra ;

    // Por cada combinación, comprobamos si es la mejor compra
    for (auto combination : combinations)
    {
        // Calculamos el beneficio de la combinación
        float beneficio = calcularBeneficio(combination, price, profit);

        // Si el coste es menor que el presupuesto y el beneficio es mayor que el de la mejor compra, actualizamos la mejor compra
        if (beneficio > mejorCompra.beneficio)
        {
            mejorCompra.acciones = combination;
            mejorCompra.beneficio = beneficio;
            mejorCompra.coste = calcularCoste(combination, price, commissions);
        }
    }

    // Imprimimos la mejor compra
    cout << "Mejor compra: ";
    for (int i = 0; i < mejorCompra.acciones.size(); i++)
    {
        cout << mejorCompra.acciones[i] << " ";
    }
    cout << endl;
    cout << "Coste: " << mejorCompra.coste << endl;
    cout << "Beneficio: " << mejorCompra.beneficio << endl;

}

void leerArchivo(vector<int> &shares, vector<float> &price, vector<float> &commissions, vector<float> &profit, string filename)
{
    ifstream file ;
    file.open(filename);

    // Si el fichero no se abre lanzamos un error
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    // Comprobamos que el primer carácter es una E
    char c;
    file >> c;
    if (c != 'E')
    {
        cerr << "Error en el formato del archivo" << endl;
        exit(1);
    }
    // Leemos el número de empresas
    int numEmpresas;
    file >> numEmpresas;
    // Iteramos sobre el número de empresas y vamos añadiendo las acciones, precio, comisiones y beneficio
    for(int i=0 ; i<numEmpresas; i++) {
        int acciones;
        float precio;
        float comision;
        float beneficio;
        file >> acciones >> precio >> comision >> beneficio;
        shares.push_back(acciones);
        price.push_back(precio);
        commissions.push_back(comision);
        profit.push_back(beneficio);
    }

}

int main(int argc, char const *argv[])
{
    vector<int> shares ;
    vector<float> price ;
    vector<float> commissions;
    vector<float> profit ;

    if(argc < 3) {
        cerr << "Uso: ./main <presupuesto> <nombre_fichero_entrada>" << endl;
    }

    // Leemos el archivo con la información
    leerArchivo(shares, price, commissions, profit, argv[2]);

    float budget = atof(argv[1]);

    // Creamos el array con todas las acciones disponibles
    vector<int> array;
    for (int i = 0; i < shares.size(); i++)
    {
        for (int j = 0; j < shares[i]; j++)
        {
            array.push_back(i);
        }
    }

    // Imprimimos el array
    cout << "Array: ";
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    // Tomamos el tiempo de inicio
    clock_t tantes = clock();

    // Llamamos a la función que nos devuelve la mejor compra posible
    printCombinations(budget, array, price, commissions, profit);

    // Tomamos el tiempo de finalización
    clock_t tdespues = clock();

    // Mostramos el tiempo de ejecución
    cout << "Tiempo de ejecución: " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

    return 0;
}