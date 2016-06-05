cmake_minimum_required(VERSION 2.8)
project(Paho)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

find_package(OpenSSL REQUIRED)

file(GLOB SOURCE_FILES 
    src/*.c)

include_directories(include)
include_directories(${OPENSSL_INCLUDE_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES} pthread)

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
