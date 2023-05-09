#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <cctype>
#include <exception>
// RANDOM
#include <cstdlib>

#ifndef STOCK
#define STOCK

class enterpriseStock {
    private:
        int n_shares;
        double profit_estimation_per_share;
        double price_per_share;
        double stock_commission;
    
        // BENEFITS - COSTS = WEIGHT maximal, more weight more tendency to buy stocks
        double weight;
        double total_costs;
    public:
        enterpriseStock(const int n, const double p, const int s, const double pe);
        double getWeigth();
        double getTotalCosts();
        double getPricePerShare();
        double getEstimatedProfit();
        double getCommision();
        int getShares();
};


class Stock {
    protected:
        double liquidity;
        std::vector<enterpriseStock> stocks_available;
        void openFile(const std::string file);
        Stock(const std::string file);
        Stock(const Stock & s);

    public:
        void printAll();
};
#endif