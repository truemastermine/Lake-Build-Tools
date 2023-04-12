cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



# Lua
# FILE(GLOB LUA_SRC libs/lua/*.c)
set(LUA_SRC 
    "libs/lua/lapi.c"
    "libs/lua/lcode.c"
    "libs/lua/lctype.c"
    "libs/lua/ldebug.c"
    "libs/lua/ldo.c"
    "libs/lua/ldump.c"
    "libs/lua/lfunc.c"
    "libs/lua/lgc.c"
    "libs/lua/llex.c"
    "libs/lua/lmem.c"
    "libs/lua/lobject.c"
    "libs/lua/lopcodes.c"
    "libs/lua/lparser.c"
    "libs/lua/lstate.c"
    "libs/lua/lstring.c"
    "libs/lua/ltable.c"
    "libs/lua/ltm.c"
    "libs/lua/lundump.c"
    "libs/lua/lvm.c"
    "libs/lua/lzio.c"
    "libs/lua/lauxlib.c"
    "libs/lua/lbaselib.c"
    "libs/lua/lcorolib.c"
    "libs/lua/ldblib.c"
    "libs/lua/liolib.c"
    "libs/lua/lmathlib.c"
    "libs/lua/loadlib.c"
    "libs/lua/loslib.c"
    "libs/lua/lstrlib.c"
    "libs/lua/ltablib.c"
    "libs/lua/lutf8lib.c"
    "libs/lua/linit.c"
)
add_library(Lua ${LUA_SRC})
target_include_directories(Lua PUBLIC libs/lua)


# Lake
project(LAKE)
add_executable(LAKE src/main.cpp src/api.cpp src/cpp.cpp)
target_include_directories(LAKE PRIVATE include libs/sol/include)
target_link_libraries(LAKE PRIVATE Lua)
