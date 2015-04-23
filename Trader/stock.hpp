#include <string>
#include <vector>
#include <iostream>
#include "position.hpp"

using namespace std;

class stock {
   public:
    stock(string abbreviation) { stock_abbreviation = abbreviation; }
    ~stock() {}

    double get_current_stock_price() { return stock_price; }
    double get_moving_average() { return moving_average; }

    void add_stock_tick(double tick) {
        prices.emplace_back(tick);
        stock_price = tick;
        determine_optimal_trades(tick);
    }

    void determine_optimal_trades(double current_stock_price) {
        for (auto& position : positions) {
            string action = position.execute_if_profit(stock_price);
            if (action == "SELL") {
                cout << "Executing sale of stock at price: " << current_stock_price
                     << endl;
            } else if (action == "HOLD") {
            }
        }
    }

    vector<position> positions{};
    vector<double> prices{};
    double stock_price;
    double moving_average;
    string stock_abbreviation;
};