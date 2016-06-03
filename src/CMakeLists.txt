cmake_minimum_required(VERSION 2.8)
project(IoTMQTTLibrary CXX)

include_directories(${CMAKE_SOURCE_DIR}/Paho/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB SOURCE_FILES 
    *.cpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CONAN_LIBS_POCO} Paho)

install(TARGETS ${CMAKE_PROJECT_NAME} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

