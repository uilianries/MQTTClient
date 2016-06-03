cmake_minimum_required(VERSION 2.8)
project(SamplesIoTMQTT CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(MQTTCLIENT_LIBRARIES ${CMAKE_PROJECT_NAME} Paho)

add_executable(SubscribeSample subscribe.cpp)
target_link_libraries(SubscribeSample ${MQTTCLIENT_LIBRARIES} ${CONAN_LIBS_OPENSSL})

add_executable(PublishSample publish.cpp)
target_link_libraries(PublishSample ${MQTTCLIENT_LIBRARIES} ${CONAN_LIBS_OPENSSL})
