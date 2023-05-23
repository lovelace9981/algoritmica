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

float calcularBeneficio(const vector<int> &acciones, const vector<float> &price, const vector<float> &profit)
{
    float beneficio = 0;
    for (int i = 0; i < acciones.size(); i++)
    {
        beneficio += acciones[i] * price[i] * profit[i];
    }
    return beneficio;
}

float calcularCoste(const vector<int> &acciones, const vector<float> &price, const vector<float> &commissions)
{
    float coste = 0;
    for (int i = 0; i < acciones.size(); i++)
    {
        coste += acciones[i] * price[i] + acciones[i] * commissions[i];
    }
    return coste;
}

// Función que devuelve una compra
void printCombinations(float budget, const vector<int> &shares, const vector<float> &price, const vector<float> &commissions, const vector<float> &profit)
{
    // Mejor compra posible
    Compra mejorCompra;

    // Iteramos sobre todas las posibilidades y comprobamos cuál es la mejor
    // Comenzamos con 0 acciones de cualquier empresa y vamos sumando
    vector<int> array = vector<int>(shares.size(), 0);
    int cont = 0;

    while (true)
    {
        cont++;
        // Imprimimos la combinación
        for (int i = 0; i < array.size(); i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;

        // Comprobamos si la combinación de acciones antes de sumar uno es mejor que la mejor compra
        float coste = calcularCoste(array, price, commissions);
        float beneficio = calcularBeneficio(array, price, profit);
        if (coste <= budget and beneficio > mejorCompra.beneficio)
        {
            mejorCompra = Compra(array, beneficio);
            mejorCompra.beneficio = beneficio;
            mejorCompra.coste = coste;
        }

        // Si no hay más combinaciones salimos del bucle
        if (array == shares)
        {
            break;
        }

        // Sumamos uno a la primera posición
        array[0]++;

        // Modificamos el array para que, si la suma de acciones es mayor que el número de acciones de la empresa, sumamos uno a la siguiente posición
        for (int i = 0; i < array.size(); i++)
        {
            if (array[i] == shares[i] and array[i + 1] != shares[i + 1])
            {
                // Imprimimos la combinación
                for (int i = 0; i < array.size(); i++)
                {
                    cout << array[i] << " ";
                }
                cout << endl;

                // Comprobamos si la combinación de acciones después de sumar uno es mejor que la mejor compra
                coste = calcularCoste(array, price, commissions);
                beneficio = calcularBeneficio(array, price, profit);
                if (coste <= budget and beneficio > mejorCompra.beneficio)
                {
                    mejorCompra = Compra(array, beneficio);
                    mejorCompra.beneficio = beneficio;
                    mejorCompra.coste = coste;
                }

                array[i] = 0;
                array[i + 1]++;
            }
        }
    }
    cout << "Total de combinaciones: " << cont << endl;

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
    ifstream file;
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
    for (int i = 0; i < numEmpresas; i++)
    {
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
    vector<int> shares;
    vector<float> price;
    vector<float> commissions;
    vector<float> profit;

    if (argc < 3)
    {
        cerr << "Uso: ./main <presupuesto> <nombre_fichero_entrada>" << endl;
        exit(1);
    }

    // Leemos el archivo con la información
    leerArchivo(shares, price, commissions, profit, argv[2]);

    float budget = atof(argv[1]);

    // Imprimimos el número de acciones que tiene cada empresa
    cout << "Acciones: ";
    for (int i = 0; i < shares.size(); i++)
    {
        cout << shares[i] << " ";
    }
    cout << endl;

    // Llamamos a la función que nos devuelve la mejor compra posible
    printCombinations(budget, shares, price, commissions, profit);

    return 0;
}