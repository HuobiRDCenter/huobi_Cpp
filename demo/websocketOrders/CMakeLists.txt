cmake_minimum_required(VERSION 3.10...3.17)
project(websocketOrders LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/huobi)

find_package(cpprestsdk REQUIRED)

link_directories(/usr/local/lib/)
link_directories(/usr/local/huobi/)

ADD_EXECUTABLE(websocketOrdersdemo websocketOrdersdemo.cpp)

target_link_libraries(websocketOrdersdemo huobi curl ssl crypto cpprestsdk::cpprest z)
