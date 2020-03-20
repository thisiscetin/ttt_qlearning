cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
 set(CMAKE_BUILD_TYPE Debug)

project(xox_qlearning)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
