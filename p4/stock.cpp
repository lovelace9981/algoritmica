#include "stock.hpp"

enterpriseStock::enterpriseStock(const int n, const double p, const int s, const double pe){
    double total_estimated_benefits_buy;

    n_shares = n;
    price_per_share = p;
    stock_commission = s;
    profit_estimation_per_share = pe;
    
    total_costs = (price_per_share * n_shares) + stock_commission;
    total_estimated_benefits_buy = profit_estimation_per_share * n_shares;

    weight = total_estimated_benefits_buy - total_costs;
}

double enterpriseStock::getWeigth(){
        return weight;

}

double enterpriseStock::getTotalCosts(){
    return total_costs;
}

double enterpriseStock::getPricePerShare(){
    return price_per_share;
}

double enterpriseStock::getEstimatedProfit(){
    return profit_estimation_per_share
}

double enterpriseStock::getTotalCosts(){
    return total_costs;
}

int enterpriseStock::getShares(){
    return n_shares;
}


//----------------- STOCK CLASS ------------------------

Stock::Stock(const std::string filename){
    openFile(filename);
}

void Stock::openFile(const std::string filename){
    std::fstream file;

    try {
        file.open(filename, std::ios::in);
    } catch (std::ifstream::failure e){
        std::cerr << "Exception opening the file " << std::endl;
    }

    bool errHeader = false;
    int n_stocks_file;
    char n_stock_converter;
    std::string line;
    std::stringstream linestringstream;

    getline(file, line);
    if (line != "STOCKS"){
        std::cerr << "Error en el header" << std::endl;
        std::terminate();
    }

    getline(file, line);
    n_stock_converter = line.at(0);
    n_stocks_file = n_stock_converter - '0';

    const std::string delim = " ";
    std::string split;
    int ns_actual, actualdelim, newdelim, actualvar;
    double pricepershare, profitpershare, commission;
    enterpriseStock * actualstock;

    ns_actual = actualdelim = newdelim = actualvar = 0;
    pricepershare = profitpershare = commission = 0.0;

    // Getting the information
    // n_shares pricepershare profitpershare commission
    for (int i = 0; i < n_stocks_file; i++){
        getline(file, line);

        while(actualdelim != line.size()){
            newdelim = line.find(delim);
            split = line.substr(actualdelim, newdelim);

            switch (actualvar) {
            case 0:
                ns_actual = std::stoi(split);
                break;
            case 1:
                pricepershare = std::stod(split);
                break;            
            case 2:
                profitpershare = std::stod(split);
                break;
            case 3:
                commission = std::stod(split);
                break;
            }
            actualvar++;
        }
        
        actualstock = new enterpriseStock(ns_actual, pricepershare, commission, profitpershare);
        stocks_available.push_back(*actualstock);
        delete actualstock;

        actualvar = actualdelim = newdelim = 0;        
    }

}

void Stock::printAll(){
    const std::string HEADER = "STOCKS AVAILABLE\n";
    const std::string COLUMNS = "WEIGHT | TOTAL COSTS | SHARE FOR SALE | PRICE PER SHARE | ESTIMATED PROFIT | COMMISSION\n";
    std::string actuals, share_s,  commision_s;
    int left_padding = HEADER.size();
    int right_padding = COLUMNS.size() - HEADER.size();
    
    std::cout << std::string(left_padding, ' ') << HEADER << std::string(left_padding, ' ') << std::endl;
    std::cout << std::string(COLUMNS.size(), '-') << std::endl;
    std::cout << COLUMNS;
    for (int i = 0; i < stocks_available.size(); i++){
        std::cout << stocks_available[i].getWeigth() << " " << stocks_available[i].getTotalCosts() \
        << " " <<  stocks_available[i].getShares() << " " << stocks_available[i].getPricePerShare() \
        << " " << stocks_available[i].getEstimatedProfit() << " " stocks_available[i].getCommission() << " ";
    }
}