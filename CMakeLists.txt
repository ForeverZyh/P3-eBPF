cmake_minimum_required(VERSION 3.16)
project(Lab4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(main main.cpp 2q/2q.cpp lru/lru.cpp)