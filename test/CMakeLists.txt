cmake_minimum_required(VERSION 2.8)
project(TestIoTMQTT CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES
        *.cpp)

find_library(GOOGLE_TEST gtest)
find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_NET PocoNet)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_PROJECT_NAME} ${POCO_FOUNDATION} ${POCO_NET} ${GOOGLE_TEST} pthread)
