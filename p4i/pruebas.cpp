#include <vector>
#include <utility>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> shares = {10, 20, 5};
    vector<int> price = {5, 3, 10};
    vector<int> commissions = {2,1,3};
    vector<int> value = {7, 5, 15};

    // Máximo número de acciones que se puede comprar en una empresa
    const int max_shares = 20;
    
    pair<int,int> cost_ben;
    cost_ben.first = 0;
    cost_ben.second = 0;
    // Creamos vector de filas de beneficio, +1 para iterar sobre la accion N=20
    vector<pair<int,int>> shares_benefit(max_shares+1, cost_ben);
    // Creamos matriz de shares que hemos comprado, cada fila es una empresa
    vector<vector<pair<int,int>>> shares_benefit_enterprise(3, shares_benefit);
    // Presupuesto
    int budget = 100;
    // Beneficio nuevo
    int benefit_new = 0;
    // Beneficio comparativo con una accion de la empresa anterior
    int benefit_anterior = 0;
    // Coste actual 
    int cost = 0;
    // Coste empresa anterior
    int cost_anterior = 0;


    // Iteramos sobre cada empresa y su cantidad de acciones
    for (int i = 0; i < shares.size(); i++){
        benefit_new = 0;
        for (int s = 0; s < shares[i]; s++){
            // intentamos meter una accion de manera adelantada
            cost += (price[i] + commissions[i]);
            benefit_new += value[i];

            // Construimos la primera fila considerando que no podemos comparar con nada anteriormente
            if (cost <= budget && i == 0){
                shares_benefit_enterprise[i][s] = benefit_new;
            }
            else if (cost <= budget && i > 0){
                cost_anterior = s*(price[i-1] + commissions[i-1]);
                // First row eval
                if (shares_benefit_enterprise[i-1][s] < benefit_new){
                    shares_benefit_enterprise[i][s] = benefit_new;
                }
                else if (shares_benefit_enterprise[i-1][s] > benefit_new && cost_anterior <= budget) {
                    // Tener una accion de la empresa anterior da mejor rendimiento
                    shares_benefit_enterprise[i][s] = shares_benefit_enterprise[i-1][s];
                }


            }
                
        }
    }
    return 0;
}
