#include <vector>

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
    return mejorCompra;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
