cmake_minimum_required(VERSION 3.10...3.17)

project(huobi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(huobi_VERSION_MAJOR 2)
set(huobi_VERSION_MINOR 3)

configure_file(
        "${PROJECT_SOURCE_DIR}/huobiConfig.h.in"
        "${PROJECT_BINARY_DIR}/huobiConfig.h"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

include_directories(/usr/local/include)
include_directories(/usr/local/opt/openssl@1.1/include)
include_directories(/opt/cpprest-2.10.16/include)


AUX_SOURCE_DIRECTORY(./src/client DIR_SRCS_CLIENT)
AUX_SOURCE_DIRECTORY(./src/ DIR_SRCS)

add_library(${PROJECT_NAME} STATIC ${DIR_SRCS} ${DIR_SRCS_CLIENT})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION huobi/
        ARCHIVE DESTINATION huobi/)

install(DIRECTORY include/ DESTINATION huobi)