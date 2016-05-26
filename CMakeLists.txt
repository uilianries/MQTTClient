cmake_minimum_required(VERSION 2.8)
project(IoTMQTTClient CXX)

option(TESTS "Generate tests" ON)
option(SAMPLES "Generate samples" ON)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_VERBOSE_MAKEFILE ON)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra -Wcast-qual -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Werror -Wno-unused")

add_subdirectory(Paho)

add_subdirectory(include)
add_subdirectory(src)

if (TESTS)
  add_subdirectory(test)
endif()

if (SAMPLES)
  add_subdirectory(samples)
endif()

