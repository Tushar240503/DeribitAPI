#ifndef API_H
#define API_H

#include <string>

class DeribitAPI {
public:
    void authenticate();
    std::string place_order(const std::string& symbol, const std::string& side, double price, double quantity);
    std::string cancel_order(const std::string& order_id);  // Cancel order function
    // Add more functions here for modifying orders and getting orderbook
};

#endif // API_H

