cmake_minimum_required(VERSION 2.8)
project(TestIoTMQTT CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES
        *.cpp)

find_library(GOOGLE_TEST gtest)
find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_NET PocoNet)

set(POCO_LIBRARIES ${POCO_FOUNDATION} ${POCO_NET})
set(MQTTCLIENT_LIBRARIES ${CMAKE_PROJECT_NAME} Paho ssl crypto pthread)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${POCO_LIBRARIES} ${MQTTCLIENT_LIBRARIES} ${GOOGLE_TEST})