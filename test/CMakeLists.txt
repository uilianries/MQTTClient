cmake_minimum_required(VERSION 2.8)
project(TestIoTMQTT CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES
        *.cpp)

find_library(GOOGLE_TEST gtest)
find_library(POCO_FOUNDATION PocoFoundation)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} IoTMQTT ${POCO_FOUNDATION} ${GOOGLE_TEST} pthread)