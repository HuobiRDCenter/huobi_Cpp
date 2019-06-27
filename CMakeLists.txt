cmake_minimum_required(VERSION 2.8)
set(platform x64)

set(CMAKE_SYSTEM_NAME Linux)

SET(CMAKE_C_COMPILER "/opt/rh/llvm-toolset-7/root/usr/bin/clang")
SET(CMAKE_C_FLAGS "-Wall -std=c99")
SET(CMAKE_C_FLAGS_DEBUG "-g")
SET(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET(CMAKE_CXX_COMPILER "/opt/rh/llvm-toolset-7/root/usr/bin/clang++")
SET(CMAKE_CXX_FLAGS "-Wall -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")


PROJECT(HuobiClient)

IF (CMAKE_BUILD_TYPE MATCHES "Release")
    SET(CMAKE_BUILD_POSTFIX "Release")
ELSEIF (CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(CMAKE_BUILD_POSTFIX "Debug")
ELSE ()
    MESSAGE(FATAL_ERROR "The CMAKE_BUILD_TYPE only supports Release or Debug")
ENDIF ()


FIND_PATH(
        LIBDECNUMBER_INCLUDE_DIR
        decNumber.h
        /usr/include/decnumber/
        /usr/local/include/decnumber/
)

include_directories(./include)
include_directories(${LIBDECNUMBER_INCLUDE_DIR})
include_directories(/usr/local/include)
include_directories(/usr/local/opt/openssl/include)

IF (ENABLE_UT)
    add_subdirectory(unittest)
ENDIF ()


AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
AUX_SOURCE_DIRECTORY(./src/Utils DIR_SRCS)


ADD_LIBRARY(${PROJECT_NAME} STATIC ${DIR_SRCS})


find_library(LIBWEBSOCKET_PATH websockets)
IF (NOT LIBWEBSOCKET_PATH)
    MESSAGE(FATAL_ERROR "libwebsockets not found")
ENDIF (NOT LIBWEBSOCKET_PATH)
MESSAGE(STATUS ${LIBWEBSOCKET_PATH} " found")

find_library(LIBSSL_PATH ssl)
IF (NOT LIBSSL_PATH)
    MESSAGE(FATAL_ERROR "libssl not found")
ENDIF (NOT LIBSSL_PATH)
MESSAGE(STATUS ${LIBSSL_PATH} " found")

find_library(LIBCRYPTO_PATH crypto)
IF (NOT LIBCRYPTO_PATH)
    MESSAGE(FATAL_ERROR "libcrypto not found")
ENDIF (NOT LIBCRYPTO_PATH)
MESSAGE(STATUS ${LIBCRYPTO_PATH} " found")

find_library(LIBCURL_PATH curl)
IF (NOT LIBCURL_PATH)
    MESSAGE(FATAL_ERROR "curl not found")
ENDIF (NOT LIBCURL_PATH)
MESSAGE(STATUS ${LIBCURL_PATH} " found")

find_library(LIBZ_PATH z)
IF (NOT LIBZ_PATH)
    MESSAGE(FATAL_ERROR "z not found")
ENDIF (NOT LIBZ_PATH)
MESSAGE(STATUS ${LIBZ_PATH} " found")

find_library(LIBDECNUMBER_PATH decnumber)
IF (NOT LIBDECNUMBER_PATH)
    MESSAGE(FATAL_ERROR "decnumber not found")
ENDIF (NOT LIBDECNUMBER_PATH)
MESSAGE(STATUS ${LIBDECNUMBER_PATH} " found")

add_definitions(-std=c++11)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY include/ DESTINATION include
        FILES_MATCHING PATTERN "*.h")

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/cert/cert.pem
        DESTINATION "/etc/huobi_cert/"
        )
