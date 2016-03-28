cmake_minimum_required(VERSION 2.8)
project(IoTMQTTLibrary CXX)

include_directories(${CMAKE_SOURCE_DIR}/Paho/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES 
    *.cpp)

find_library(POCO_UTIL PocoUtil)
find_library(POCO_XML PocoXML)
find_library(POCO_JSON PocoJSON)
find_library(POCO_FOUNDATION PocoFoundation)
set(POCO_LIBRARIES ${POCO_UTIL} ${POCO_XML} ${POCO_JSON} ${POCO_FOUNDATION})

add_library(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${POCO_LIBRARIES} Paho)

install(TARGETS ${CMAKE_PROJECT_NAME} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

