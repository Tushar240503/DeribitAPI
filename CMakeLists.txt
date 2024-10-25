cmake_minimum_required(VERSION 3.10)
project(DeribitTradingSystem)

# Set C++ standard and compiler optimization flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

# Include directories for headers
include_directories(include)
include_directories(include/websocketpp/websocketpp)  # Add this line for WebSocket++

# Add external dependencies for WebSocket++ and Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Add the executable and link it to source files
add_executable(deribit_trading_system 
    src/main.cpp 
    src/api.cpp 
    src/websocket.cpp
)

# Link the executable with curl (for HTTP requests) and Boost (for WebSocket++)
find_package(CURL REQUIRED)
target_link_libraries(deribit_trading_system CURL::libcurl ${Boost_LIBRARIES})

