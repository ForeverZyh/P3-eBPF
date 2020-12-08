cmake_minimum_required(VERSION 3.16)
project(Lab4)

set(CMAKE_CXX_STANDARD 14)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(lru
        lru/lru.cpp)
add_executable(2q
        2q/2q.cpp)
