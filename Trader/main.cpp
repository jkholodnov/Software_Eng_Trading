#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

    string line{""};
    while (getline(inputs, line)) {
        auto x = line.find(",");
        auto g = line.substr(0, x);
        cout << g << endl;
    }
}