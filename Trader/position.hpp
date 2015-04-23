#include <string>
using namespace std;

class position {
   public:
    position() {}
    ~position() {}

    string execute_if_profit(double stock_price) {
        if (isactive == false) {
            return "SOLD";
        }
        if (stock_price > buy_price) {
            isactive = false;
            return "SELL";
        } else {
            return "HOLD";
        }
    }

   private:
    double buy_price;
    bool isactive = true;
};