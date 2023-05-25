#include <vector>
#include <iostream>
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

// Función que calcula la mejor compra posible con Programacion Dinamica, devuelve una compra
// Como argumentos tiene, el vector que almacena las mejores compras, el presupuesto, el intervalo de presupuestos, el número de acciones por empresa,
// el precio de las acciones, las comisiones y el porcentaje de beneficio de las acciones.
Compra calculoPD(vector<vector<Compra>> &mem, float intervalo, float budget, int empresa, const vector<int> &shares, const vector<float> &price, const vector<float> &commissions, const vector<float> &profit)
{
    // Si ya hemos calculado la mejor compra para ese presupuesto, la devolvemos
    if (mem[empresa][(int)(budget / intervalo)].beneficio != -1)
    {
        return mem[empresa][(int)(budget / intervalo)];
    }

    if(empresa == 0) 
        return mem[empresa][(int)(budget / intervalo)];

    // Si no, calculamos la mejor compra posible
    Compra mejorCompra;

    // Tenemos tres casos en la ecuación de recurrencia, calculamos los tres y sacamos el máximo
    // Caso 1: No compramos ninguna acción de la empresa, es decir, tenemos en cuenta la mejor opción de la fila anterior
    Compra caso1 = calculoPD(mem, intervalo, budget, empresa - 1, shares, price, commissions, profit);

    /*
        ------------------------------------------------------
    */

    // Caso 2: Teniendo en cuenta la mejor compra del presupuesto anterior, compramos el mayor número de acciones de la empresa disponibles y que no se pasen del presupuesto
    Compra caso2;
    Compra casoAnterior = calculoPD(mem, intervalo, budget - intervalo, empresa, shares, price, commissions, profit);
    // Calculamos las acciones que tendríamos disponibles si compraramos con el presupuesto anterior
    vector<int> accionesDisponibles = shares;
    for (int i = 0; i < accionesDisponibles.size(); i++)
    {
        accionesDisponibles[i] -= casoAnterior.acciones[i];
        if (accionesDisponibles[i] < 0)
            accionesDisponibles[i] = 0;
    }
    // Calculamos el presupuesto extra que tenemos para comprar acciones
    float presupuestoExtra = intervalo + budget - casoAnterior.coste;

    // Calculamos el número de acciones de la empresa que podemos comprar con el presupuesto extra
    int accionesCompradas = (int)(presupuestoExtra / (price[empresa] + commissions[empresa]));

    // Tenemos que comprobar si podemos comprar más acciones de las disponibles
    accionesCompradas >= accionesDisponibles[empresa] ? accionesCompradas = accionesDisponibles[empresa] : accionesCompradas = accionesCompradas;

    // Si podemos comprar más de 0 entradas, calculamos el beneficio de la compra
    if (accionesCompradas > 0)
    {
        // Calculamos el beneficio de la compra
        float beneficio = accionesCompradas * price[empresa] * profit[empresa];

        // Actualizamos la variable de caso 2 poniendole el nuevo beneficio
        caso2 = casoAnterior;
        caso2.beneficio += beneficio;
        caso2.coste += accionesCompradas * (price[empresa] + commissions[empresa]);
        caso2.acciones[empresa] += accionesCompradas;
    }
    else
    {
        caso2 = casoAnterior;
    }

    /*
        ------------------------------------------------------
    */

    // Caso 3: Comprobamos el beneficio de comprar con el presupuesto anterior, la mejor opción con el presupuesto restante teniendo en cuenta la empresa anterior
    // Reutilizamos variables de presupuestoExtra y compraAnterior, pues son los mismos valores y no se modifican
    Compra caso3;

    // Calculamos el beneficio que podemos obtener teniendo en cuenta la empresa anterior con el presupuesto restante
    Compra compraEmpresaAnterior = calculoPD(mem, intervalo, (int)(presupuestoExtra / intervalo), empresa - 1, shares, price, commissions, profit);

    // Comprobamos si hay suficientes acciones disponibles para comprar la compraEmpresaAnterior
    accionesDisponibles = shares;
    for (int i = 0; i < accionesDisponibles.size(); i++)
    {
        accionesDisponibles[i] -= compraEmpresaAnterior.acciones[i] - casoAnterior.acciones[i];
        if (accionesDisponibles[i] < 0)
            accionesDisponibles[i] = 0;
    }

    // Comprobamos si se puede comprar la combinación de acciones de Empresa anterior
    for (int i = 0; i < accionesDisponibles.size(); i++)
    {
        if (accionesDisponibles[i] >= compraEmpresaAnterior.acciones[i])
            accionesDisponibles[i] = compraEmpresaAnterior.acciones[i];
    }

    // Calculamos el nuevo beneficio y coste de la compra
    float beneficio = 0;
    float coste = 0;
    for (int i = 0; i < accionesDisponibles.size(); i++)
    {
        beneficio += accionesDisponibles[i] * price[i] * profit[i];
        coste += accionesDisponibles[i] * (price[i] + commissions[i]);
    }
    // Actualizamos la variable de caso 3 poniendole el nuevo beneficio
    caso3 = casoAnterior;
    caso3.beneficio += beneficio;
    caso3.coste += coste;
    for (int i = 0; i < accionesDisponibles.size(); i++)
    {
        caso3.acciones[i] += accionesDisponibles[i];
    }

    /*
        ------------------------------------------------------
    */

    // Calculamos de los tres casos, cual es el que nos da más beneficio y lo guardamos en la variable mejorCompra
    if (caso1.beneficio > caso2.beneficio)
    {
        if (caso1.beneficio > caso3.beneficio)
        {
            mejorCompra = caso1;
        }
        else
        {
            mejorCompra = caso3;
        }
    }
    else
    {
        if (caso2.beneficio > caso3.beneficio)
        {
            mejorCompra = caso2;
        }
        else
        {
            mejorCompra = caso3;
        }
    }

    // Guardamos la mejor compra para ese presupuesto y la devolvemos
    mem[empresa][(int)(budget / intervalo)] = mejorCompra;

    // Imprimimos el header de la tabla con los valores de los intervalos
    cout << "Int.\t";
    for (int i = 0; i < mem[0].size(); i++)
    {
        cout << i * intervalo << "\t";
    }
    cout << endl;

    // Imprimimos la tabla después de calcular la mejor compra
    for(int i = 0; i < mem.size(); i++){
        for(int j = 0; j < mem[i].size(); j++){
            cout << i << "\t";
            cout << mem[i][j].beneficio << "\t";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl ;
    return mejorCompra;
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

void sort(vector<pair<float, int>> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            if (v[j].first > v[j + 1].first)
            {
                pair<float, int> aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    const int NUM_INTERVALOS = 2;
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

    // Ordenamos el orden de las empresas en orden ascendente de (beneficio*precio)/(precio+comision)
    vector<pair<float, int>> ordenEmpresas;
    for (int i = 0; i < shares.size(); i++)
    {
        ordenEmpresas.push_back(make_pair((profit[i] * price[i]) / (price[i] + commissions[i]), i));
    }

    // Llamamos a la función para ordenar el vector
    sort(ordenEmpresas);

    vector<int> sharesOrden;
    vector<float> priceOrden;
    vector<float> commissionsOrden;
    vector<float> profitOrden;
    // Ordenamos los vectores de acciones, precio, comisiones y beneficio en el orden que nos ha dado la función sort
    for (int i = 0; i < ordenEmpresas.size(); i++)
    {
        sharesOrden.push_back(shares[ordenEmpresas[i].second]);
        priceOrden.push_back(price[ordenEmpresas[i].second]);
        commissionsOrden.push_back(commissions[ordenEmpresas[i].second]);
        profitOrden.push_back(profit[ordenEmpresas[i].second]);
    }

    // Obtenemos el presupuesto especificado por el usuario
    float budget = atof(argv[1]);

    // Inicializamos la matriz de memorización
    vector<vector<Compra>> mem = vector<vector<Compra>>(shares.size());

    // Inicializamos la matriz de memorización con todo a -1
    for (int i = 0; i < mem.size(); i++)
    {
        // Tendremos NUM_INTERVALOS + 1 columnas, pues el presupuesto va desde el intervalo 0 al NUM_INTERVALOS, que sería el presupuesto que se le pasa a el programa
        mem[i] = vector<Compra>(NUM_INTERVALOS + 1);
        for (int j = 0; j < mem[i].size(); j++)
        {
            mem[i][j].beneficio = -1;
            mem[i][j].coste = -1;
            mem[i][j].acciones = vector<int>(shares.size());
        }
    }

    // Tendremos NUM_INTERVALOS columnas, por lo que los intervalos serán la división del presupuesto entre NUM_INTERVALOS
    float intervalo = budget / NUM_INTERVALOS;

    // Calculamos los valores de la primera fila de la matriz de memorización, pues es el caso base donde el beneficio es el máximo que se puede obtener con el presupuesto de esa columna comprando acciones de la empresa 0
    for (int i = 0; i < mem[0].size(); i++)
    {
        int accionesComprables = (int)((intervalo*i) / (price[0] + commissions[0]));
        if(accionesComprables > shares[0])
            accionesComprables = shares[0];
        mem[0][i].beneficio = accionesComprables * price[0] * profit[0];
        mem[0][i].coste = accionesComprables * (price[0] + commissions[0]);
        mem[0][i].acciones[0] = accionesComprables;
    }

    // Los valores de la la columna 0 tienen que ser 0 para cualquier empresa, pues con presupuesto 0 no se puede comprar ninguna acción
    for (int i = 0; i < mem.size(); i++)
    {
        mem[i][0].beneficio = 0;
        mem[i][0].coste = 0;
    }

    // Calculamos la mejor compra teniendo en cuenta todas las empresas para el presupuesto que se le pasa al programa
    Compra mejorCompra = calculoPD(mem, intervalo, budget, sharesOrden.size() - 1, sharesOrden, priceOrden, commissionsOrden, profitOrden);

    // Imprimimos el beneficio y el coste de la mejor compra, además de la cantidad de acciones que se han comprado de cada empresa
    cout << "Beneficio: " << mejorCompra.beneficio << endl;
    cout << "Coste: " << mejorCompra.coste << endl;
    cout << "Acciones: ";
    for (int i = 0; i < mejorCompra.acciones.size(); i++)
    {
        cout << mejorCompra.acciones[i] << " ";
    }
    cout << endl;
    
    return 0;
}
