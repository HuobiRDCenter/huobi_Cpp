cmake_minimum_required(VERSION 2.8)
set(platform x64)
PROJECT(HuobiClient)

IF (CMAKE_BUILD_TYPE MATCHES "Release")
    SET(CMAKE_BUILD_POSTFIX "Release")
ELSEIF(CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(CMAKE_BUILD_POSTFIX "Debug")
ELSE()
    MESSAGE(FATAL_ERROR "The CMAKE_BUILD_TYPE only supports Release or Debug")
ENDIF()


include_directories(./include)
include_directories(./3rdparty/libwebsockets/include)
include_directories(./3rdparty/curl/include)
include_directories(./3rdparty/openssl/include)
include_directories(./3rdparty/zlib/include)
include_directories(./3rdparty/libdecnumber/include)

add_subdirectory(unittest)


AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
AUX_SOURCE_DIRECTORY(./src/Utils DIR_SRCS)


ADD_LIBRARY(${PROJECT_NAME} STATIC ${DIR_SRCS})


find_library(LIBWEBSOCKET_PATH websockets ./3rdparty/libwebsockets/lib)
IF(NOT LIBWEBSOCKET_PATH)
MESSAGE(FATAL_ERROR "libwebsockets not found")
ENDIF(NOT LIBWEBSOCKET_PATH)
MESSAGE(STATUS ${LIBWEBSOCKET_PATH} " found")

find_library(LIBSSL_PATH ssl ../3rdparty/openssl/lib)
IF(NOT LIBSSL_PATH)
MESSAGE(FATAL_ERROR "libssl not found")
ENDIF(NOT LIBSSL_PATH) 
MESSAGE(STATUS ${LIBSSL_PATH} " found")

find_library(LIBCRYPTO_PATH crypto ../3rdparty/openssl/lib)
IF(NOT LIBCRYPTO_PATH)
MESSAGE(FATAL_ERROR "libcrypto not found")
ENDIF(NOT LIBCRYPTO_PATH) 
MESSAGE(STATUS ${LIBCRYPTO_PATH} " found")

find_library(LIBCURL_PATH curl ../3rdparty/curl/lib)
IF(NOT LIBCURL_PATH)
MESSAGE(FATAL_ERROR "curl not found")
ENDIF(NOT LIBCURL_PATH) 
MESSAGE(STATUS ${LIBCURL_PATH} " found")

find_library(LIBZ_PATH z ../3rdparty/zlib/lib)
IF(NOT LIBZ_PATH)
MESSAGE(FATAL_ERROR "z not found")
ENDIF(NOT LIBZ_PATH) 
MESSAGE(STATUS ${LIBZ_PATH} " found")

find_library(LIBDECNUMBER_PATH decnumber ../3rdparty/libdecnumber/lib)
IF(NOT LIBDECNUMBER_PATH)
MESSAGE(FATAL_ERROR "decnumber not found")
ENDIF(NOT LIBDECNUMBER_PATH) 
MESSAGE(STATUS ${LIBDECNUMBER_PATH} " found")

add_definitions(-std=c++11)

install(FILES ${CMAKE_BINARY_DIR}/libHuobiClient.a
    DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_POSTFIX}"
)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cert/cert.pem
    DESTINATION "/etc/huobi_cert/"
)
