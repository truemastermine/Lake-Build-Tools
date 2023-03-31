cmake_minimum_required(VERSION 4.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)






project(LAKE)
add_executable(LAKE src/main.cpp)
target_include_directories(LAKE PRIVATE include)