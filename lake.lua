lmake("1.0.0", "build")

local lua = project("C")

lua:sourceDir("libs/lua/", ".c")
lua:includeDir("libs/lua")


local lake = project("c++")
lake:version("cxx17")

lake:sourceDir("src", ".cpp")
lake:includeDir("includes")
lake:link(lua)

lake:build("LakeBin.o")
