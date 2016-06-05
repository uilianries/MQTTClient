cmake_minimum_required(VERSION 2.8)
project(IoTMQTTLibrary CXX)

include_directories(${CMAKE_SOURCE_DIR}/Paho/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${Poco_INCLUDE_DIRS})

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Poco_LIBRARIES} Paho)

install(TARGETS ${CMAKE_PROJECT_NAME} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

