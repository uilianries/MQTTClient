cmake_minimum_required(VERSION 2.8)
project(SamplesIoTMQTT CXX)

find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_UTIL PocoUtil)

set(POCO_LIBRARIES ${POCO_FOUNDATION} ${POCO_UTIL})
set(MQTTCLIENT_LIBRARIES ${CMAKE_PROJECT_NAME} Paho ssl crypto pthread)

add_executable(SubscribeSample subscribe.cpp)
target_link_libraries(SubscribeSample ${MQTTCLIENT_LIBRARIES} ${POCO_LIBRARIES})

add_executable(PublishSample publish.cpp)
target_link_libraries(PublishSample ${MQTTCLIENT_LIBRARIES} ${POCO_LIBRARIES})