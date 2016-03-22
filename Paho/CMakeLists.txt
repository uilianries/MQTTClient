cmake_minimum_required(VERSION 2.8)
project(Paho)

find_library(SSL_LIBRARY ssl)
find_library(CRYPTO_LIBRARY crypto)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -DOPENSSL")

file(GLOB SOURCE_FILES 
    src/*.c)

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SSL_LIBRARY} ${CRYPTO_LIBRARY})
