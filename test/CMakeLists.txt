cmake_minimum_required(VERSION 2.8)
project(TestIoTMQTT CXX)

find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${Poco_INCLUDE_DIRS})

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(MQTTCLIENT_LIBRARIES ${CMAKE_PROJECT_NAME} Paho)

message("POCO LIBS: ${Poco_LIBRARIES}")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MQTTCLIENT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${Poco_LIBRARIES})
