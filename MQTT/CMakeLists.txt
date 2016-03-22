cmake_minimum_required(VERSION 2.8)
project(IoTMQTT CXX)

add_subdirectory(Paho)

include_directories(Paho/include)
include_directories(include)

file(GLOB SOURCE_FILES 
    src/*.cpp)

find_library(POCO_UTIL PocoUtil)
find_library(POCO_XML PocoXML)
find_library(POCO_JSON PocoJSON)
find_library(POCO_FOUNDATION PocoFoundation)
set(POCO_LIBRARIES ${POCO_UTIL} ${POCO_XML} ${POCO_JSON} ${POCO_FOUNDATION})

add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${POCO_LIBRARIES} Paho)

install(TARGETS ${PROJECT_NAME} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME})


