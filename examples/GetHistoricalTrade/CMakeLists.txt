cmake_minimum_required(VERSION 2.8)
set(platform x64)

PROJECT(GetHistoricalTrade)

IF(HUOBI_CLIENT_DIR)
    MESSAGE("Load the HuobiClient module from ${HUOBI_CLIENT_DIR}")
ELSE()
    MESSAGE(FATAL_ERROR "HUOBI_CLIENT_DIR must be defined in command.")
ENDIF()

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})

IF (CMAKE_BUILD_TYPE MATCHES "Release")
    SET(CMAKE_BUILD_POSTFIX ${CMAKE_BUILD_TYPE})
ELSEIF(CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(CMAKE_BUILD_POSTFIX ${CMAKE_BUILD_TYPE})
ELSE()
    MESSAGE(FATAL_ERROR "The CMAKE_BUILD_TYPE only supports Release or Debug")
ENDIF()


find_library(LIBHUOBICLIENT_PATH HuobiClient ${HUOBI_CLIENT_DIR}/lib/${CMAKE_BUILD_POSTFIX})
IF(NOT LIBHUOBICLIENT_PATH)
message(${HUOBI_CLIENT_DIR}/lib/${CMAKE_BUILD_POSTFIX})
MESSAGE(FATAL_ERROR "HuobiClient not found")
ENDIF(NOT LIBHUOBICLIENT_PATH)
MESSAGE(STATUS ${LIBHUOBICLIENT_PATH} " found")
include_directories(${HUOBI_CLIENT_DIR}/include)


find_library(LIBWEBSOCKET_PATH websockets ${HUOBI_CLIENT_DIR}/3rdparty/libwebsockets/lib)
IF(NOT LIBWEBSOCKET_PATH)
MESSAGE(FATAL_ERROR "libwebsockets not found")
ENDIF(NOT LIBWEBSOCKET_PATH)
MESSAGE(STATUS ${LIBWEBSOCKET_PATH} " found")
include_directories(${HUOBI_CLIENT_DIR}/3rdparty/libwebsockets/include)

find_library(LIBSSL_PATH ssl ${HUOBI_CLIENT_DIR}/3rdparty/openssl/lib)
IF(NOT LIBSSL_PATH)
MESSAGE(FATAL_ERROR "libssl not found")
ENDIF(NOT LIBSSL_PATH) 
MESSAGE(STATUS ${LIBSSL_PATH} " found")
include_directories(${HUOBI_CLIENT_DIR}/3rdparty/openssl/include)

find_library(LIBCRYPTO_PATH crypto ${HUOBI_CLIENT_DIR}/3rdparty/openssl/lib)
IF(NOT LIBCRYPTO_PATH)
MESSAGE(FATAL_ERROR "libcrypto not found")
ENDIF(NOT LIBCRYPTO_PATH) 
MESSAGE(STATUS ${LIBCRYPTO_PATH} " found")

find_library(LIBCURL_PATH curl ${HUOBI_CLIENT_DIR}/3rdparty/curl/lib)
IF(NOT LIBCURL_PATH)
MESSAGE(FATAL_ERROR "curl not found")
ENDIF(NOT LIBCURL_PATH) 
MESSAGE(STATUS ${LIBCURL_PATH} " found")
include_directories(${HUOBI_CLIENT_DIR}/3rdparty/curl/include)

find_library(LIBZ_PATH z ${HUOBI_CLIENT_DIR}/3rdparty/zlib/lib)
IF(NOT LIBZ_PATH)
MESSAGE(FATAL_ERROR "z not found")
ENDIF(NOT LIBZ_PATH) 
MESSAGE(STATUS ${LIBZ_PATH} " found")
include_directories(${HUOBI_CLIENT_DIR}/3rdparty/zlib/include)

find_library(LIBDECNUMBER_PATH decnumber ${HUOBI_CLIENT_DIR}/3rdparty/libdecnumber/lib)
IF(NOT LIBDECNUMBER_PATH)
MESSAGE(FATAL_ERROR "decnumber not found")
ENDIF(NOT LIBDECNUMBER_PATH) 
MESSAGE(STATUS ${LIBDECNUMBER_PATH} " found")
include_directories(${HUOBI_CLIENT_DIR}/3rdparty/libdecnumber/include)

add_definitions(-std=c++11)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBHUOBICLIENT_PATH} ${LIBDECNUMBER_PATH} ${LIBSSL_PATH} ${LIBCRYPTO_PATH} ${LIBWEBSOCKET_PATH} ${LIBCURL_PATH} ${LIBZ_PATH})

