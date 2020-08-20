cmake_minimum_required(VERSION 3.10...3.17)
project(demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/huobi)

add_subdirectory(account)
add_subdirectory(crossmargin)
add_subdirectory(isolatedmargin)
add_subdirectory(market)
add_subdirectory(reference)
add_subdirectory(trade)
add_subdirectory(wallet)
add_subdirectory(websocketAsset)
add_subdirectory(websocketMarket)
add_subdirectory(websocketOrders)

find_package(cpprestsdk REQUIRED)

link_directories(/usr/local/lib/)
link_directories(/usr/local/huobi/)
