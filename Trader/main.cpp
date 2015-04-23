#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include "stock.hpp"

using namespace std;

int main() {
    char selection;
    cout << "Which trading system would you like to use? (S = Scraper or P = Portfolio)"
         << endl;
    cin >> selection;

    ifstream inputs;
    if (selection == 'S') {
        inputs.open("../Scraper/Scraper_Output.csv");
    } else if (selection == 'P') {
        inputs.open("../Portfolio/Portfolio_Output.csv");
    } else {
        cout << "Please check your input and try again." << endl;
        return 0;
    }

    vector<stock> Stocks_being_monitored{};

    string g;
    while (inputs >> g) {
        auto pos = g.find(",");
        auto stocksymbol = g.substr(0, pos);
        Stocks_being_monitored.emplace_back(stocksymbol);
    }

    cout << "READ IN STOCK SYMBOLS. Proceeding to execute trades." << endl;

    time_t now = time(0);

    tm *ltm = localtime(&now);
    cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;

    bool stock_hours = true;
    while (stock_hours) {
        cout << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
        if (ltm->tm_hour < 9) {
            cout << "Stock market hasnt opened yet." << endl;
            break;
        }
        if (ltm->tm_hour > 16 && ltm->tm_min > 30) {
            cout << "Stock market has closed." << endl;
            break;
        }
        cout << "Stock market is open. Executing trades." << endl;
        for (auto &stock : Stocks_being_monitored) {
            // GET THE CURRENT PRICE OF STOCK...//
            double current_price = stock.price + (rand() % 5);
            stock.add_stock_tick(current_price);
        }

        now = time(0);
        ltm = localtime(&now);
    }
}