cmake_minimum_required(VERSION 2.8)
project(TestIoTMQTT CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES
        *.cpp)

set(MQTTCLIENT_LIBRARIES ${CMAKE_PROJECT_NAME} Paho)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MQTTCLIENT_LIBRARIES} ${CONAN_LIBS_GTEST})
