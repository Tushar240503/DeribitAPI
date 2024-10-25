#include "api.h"
#include <curl/curl.h>
#include <iostream>

// Constants for the client credentials
const std::string CLIENT_ID = "bkXIc3yR";
const std::string CLIENT_SECRET = "voUSPPiJz3fb-zVBbq5RuFgxw3chWHR6JRUyQaGAtjo";

// Callback function to handle libcurl response
size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

// Authenticate to Deribit API
void DeribitAPI::authenticate() {
    CURL* curl = curl_easy_init();
    if (curl) {
        std::string url = "https://test.deribit.com/api/v2/public/auth";
        
        std::string post_data = R"({"grant_type": "client_credentials", "client_id": ")" + CLIENT_ID + R"(", "client_secret": ")" + CLIENT_SECRET + R"("})";
        
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
        
        // Set headers to indicate JSON format
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Auth response: " << response << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        
        // TODO: Add JSON parsing here to handle the authentication token.
    }
}



// Function to place an order
std::string DeribitAPI::place_order(const std::string& symbol, const std::string& side, double price, double quantity) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = (side == "buy") ? "https://test.deribit.com/api/v2/private/buy"
                                          : "https://test.deribit.com/api/v2/private/sell";
        std::string post_data = "instrument_name=" + symbol + "&amount=" + std::to_string(quantity) + "&price=" + std::to_string(price);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Add authorization header here if needed
        // Example: curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

// Function to cancel an order
std::string DeribitAPI::cancel_order(const std::string& order_id) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = "https://test.deribit.com/api/v2/private/cancel";
        std::string post_data = "order_id=" + order_id;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Add authorization header here if needed
        // Example: curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;  // This response will contain the result of the cancel operation
}

