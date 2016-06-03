cmake_minimum_required(VERSION 2.8)
project(Paho)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -DOPENSSL")

file(GLOB SOURCE_FILES 
    src/*.c)

include_directories(include)

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_OPENSSL})

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
