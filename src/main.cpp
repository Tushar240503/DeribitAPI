#include "api.h"
#include "websocket.h"
#include <iostream>

int main() {
    std::cout << "Starting Deribit Trading System..." << std::endl;

    // Initialize API
    DeribitAPI api;
    api.authenticate();

    // Place an example order
    std::string order_response = api.place_order("BTC-PERPETUAL", "buy", 20000.0, 0.5);
    std::cout << "Order Response: " << order_response << std::endl;

    // Start WebSocket server for real-time updates
    start_websocket_server();

    return 0;
}

