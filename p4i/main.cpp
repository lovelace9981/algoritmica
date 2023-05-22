#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Compra
{
    vector<int> acciones;
    float beneficio = 0;
    float coste = 0;

    Compra() {}
    Compra(vector<int> acciones, int beneficio) : acciones(acciones), beneficio(beneficio) {}
};

float calcularBeneficio (vector<int> acciones, vector<float> price, vector<float> profit)
{
    float beneficio = 0;
    for (int i = 0; i < acciones.size(); i++)
    {
        beneficio +=  price[acciones[i]] * profit[acciones[i]];
    }
    return beneficio;
}

float calcularCoste(vector<int> acciones, vector<float> price, vector<float> commissions)
{
    float coste = 0;
    for (int i = 0; i < acciones.size(); i++)
    {
        coste += price[acciones[i]] + commissions[acciones[i]];
    }
    return coste;
}

// Función que devuelve una compra
void printCombinations(float budget, vector<int> array, vector<float> price, vector<float> commissions , vector<float> profit)
{
    // Mejor compra posible
    Compra mejorCompra ;
    // Create a vector to store the combinations.
    vector<vector<int>> combinations;

    // Iterate over all possible combinations.
    for (int i = 0; i < (1 << array.size()); i++)
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

        float coste = calcularCoste(combination, price, commissions);
        float beneficio = calcularBeneficio(combination, price, profit);

        // Si el precio de la combinación de acciones es menor que el presupuesto y el beneficio es mayor que el actual, cambiamos la mejor compra a ésta
        if (coste <= budget && mejorCompra.beneficio < beneficio)
        {
            // Actualizamos la mejor compra
            mejorCompra.acciones = combination;
            mejorCompra.coste = coste;
            mejorCompra.beneficio = beneficio;
        }


        // // If the combination has the desired size, add it to the list of combinations.
        // if (combination.size() == r)
        // {
        //     combinations.push_back(combination);
        // }
    }

    // // Print the list of combinations.
    // for (vector<int> combination : combinations)
    // {
    //     for (int element : combination)
    //     {
    //         cout << element << " ";
    //     }
    //     cout << endl;
    // }
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

    // Llamamos a la función que nos devuelve la mejor compra posible
    printCombinations(budget, array, price, commissions, profit);

    return 0;
}