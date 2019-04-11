cmake_minimum_required(VERSION 2.8)
set(platform x64)
PROJECT(decnumber)


SET(DIR_SRCS ./src/decContext.c ./src/decDouble.c ./src/decNumber.c ./src/decPacked.c ./src/decQuad.c ./src/decSingle.c ./src/decimal128.c ./src/decimal32.c ./src/decimal64.c)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${DIR_SRCS})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY src/ DESTINATION include/decnumber
    FILES_MATCHING PATTERN "*.h" PATTERN "*.c")