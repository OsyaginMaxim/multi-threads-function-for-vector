cmake_minimum_required(VERSION 3.8)
project(AdvancedCppTask6)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(AdvancedCppTask6 ${SOURCE_FILES})
find_package( Threads REQUIRED )
