cmake_minimum_required(VERSION 3.10)

project(hello)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_BUILD_TYPE "Debug")

add_executable(hello hello.cpp)

TARGET_LINK_LIBRARIES(hello pthread)


