cmake_minimum_required(VERSION 3.10...3.17)
project(crossmargin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/huobi)

find_package(cpprestsdk REQUIRED)

link_directories(/usr/local/lib/)
link_directories(/usr/local/huobi/)


ADD_EXECUTABLE(crossmargindemo crossmargindemo.cpp)

target_link_libraries(crossmargindemo huobi curl ssl crypto cpprestsdk::cpprest z)
