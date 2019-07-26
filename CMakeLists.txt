cmake_minimum_required(VERSION 2.8)

#设置编译器
IF (CMAKE_COMPILER_TYPE MATCHES "GCC")
    SET(CMAKE_C_COMPILER "gcc")
    SET(CMAKE_CXX_COMPILER "g++")
ELSEIF (CMAKE_COMPILER_TYPE MATCHES "CLANG")
    SET(CMAKE_C_COMPILER "clang")
    SET(CMAKE_CXX_COMPILER "clang++")
ENDIF ()

SET(CMAKE_C_FLAGS "-Wall -std=c99")
SET(CMAKE_C_FLAGS_DEBUG "-g")
SET(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET(CMAKE_CXX_FLAGS "-Wall -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")


#判断操作系统
IF (WIN32)
    MESSAGE(STATUS "Now is windows")
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS's. Including aPPLE os x  and CygWin")
ENDIF ()

if (UNIX AND NOT APPLE)
    set(platform x64)
    set(LINUX TRUE)
endif ()

if (APPLE)
endif ()


if (LINUX)
    message(STATUS "当前操作系统: Linux")
endif ()

if (APPLE)
    message(STATUS "当前操作系统: MacOS")
endif ()

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")


PROJECT(HuobiClient)

set(CURRENT_VERSION 1)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_BINARY_DIR}/config.h")

include_directories("${PROJECT_BINARY_DIR}")

if (LINUX)
    execute_process(COMMAND sh ../getOpensslVersion.sh
            OUTPUT_VARIABLE OPENSSL_VERSION
            ERROR_QUIET)

    if (OPENSSL_VERSION EQUAL 1.1)
        MESSAGE(STATUS "openssl version is 1.1.x")
        add_definitions(-DOPENSSL_VERSION_1_1)
    elseif (OPENSSL_VERSION EQUAL 1.0)
        MESSAGE(STATUS "openssl version is 1.0.x")
        add_definitions(-DOPENSSL_VERSION_1_0)
    else ()
        MESSAGE(FATAL_ERROR "openssl version should be 1.0.x or 1.1.x")
    endif ()
elseif (APPLE)
    MESSAGE(STATUS "openssl version is 1.0.x")
    add_definitions(-DOPENSSL_VERSION_1_0)
endif ()

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

if (APPLE)
    include_directories(/usr/local/opt/openssl/include)
endif ()


IF (ENABLE_UT)
    add_subdirectory(unittest)
ENDIF ()


AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
AUX_SOURCE_DIRECTORY(./src/Utils DIR_SRCS)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${DIR_SRCS})

find_package(Boost)
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
