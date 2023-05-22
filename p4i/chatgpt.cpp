#include<bits/stdc++.h>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

pair<int, vector<int>> calculate_profit(int n, int budget, vector<int>& stocks, vector<int>& prices, vector<int>& profits, vector<int>& commission, vector<int> portfolio = {}) {
    if (n == 0 || budget == 0)
        return make_pair(0, portfolio);

    if (prices[n - 1] + commission[n - 1] > budget) 
        return calculate_profit(n - 1, budget, stocks, prices, profits, commission, portfolio);
    
    pair<int, vector<int>> max_profit;
    max_profit.first = INT_MIN;

    // itera sobre los stocks
    // Mientras que no se pase de precios + comision, es decir multiplica cada stock de la empresa N-1
    // Si se pasa del budget se quita, no se considera en el portafolio
    for(int i=0; i<=stocks[n - 1] && i*(prices[n - 1] + commission[n - 1]) <= budget; i++) {
        vector<int> new_portfolio = portfolio;
        
        new_portfolio.push_back(i);
        
        pair<int, vector<int>> profit_including_n = calculate_profit(n - 1, budget - i*(prices[n - 1] + commission[n - 1]), stocks, prices, profits, commission, new_portfolio);
        
        // Recoge el beneficio
        profit_including_n.first += i * profits[n - 1];

        if(profit_including_n.first > max_profit.first) {
            max_profit = profit_including_n;
        }
    }

    return max_profit;
}

int main() {
    int N = 3;
    int budget = 100;
    vector<int> stocks = {10, 20, 30};
    vector<int> prices = {20, 30, 50};
    vector<int> profits = {10, 20, 30};
    vector<int> commission = {1, 2, 3};

    for (int i = 0; i < N; ++i) 
        profits[i] = profits[i] * prices[i] / 100;

    pair<int, vector<int>> result = calculate_profit(N, budget, stocks, prices, profits, commission);
    cout << "Max profit: " << result.first << "\n";
    cout << "Number of stocks to buy from each company (0-indexed): ";
    for (int i = 0; i < result.second.size(); ++i)
        cout << result.second[i] << " ";    
    cout << "\n";

    return 0;
}