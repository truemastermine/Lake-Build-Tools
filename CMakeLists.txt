cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



# Lua
FILE(GLOB LUA_SRC libs/lua/*.c)
add_library(Lua ${LUA_SRC})
target_include_directories(Lua PUBLIC libs/lua)


# Lake
project(LAKE)
add_executable(LAKE src/main.cpp)
target_include_directories(LAKE PRIVATE include libs/sol/include)
target_link_libraries(LAKE PRIVATE Lua)
