lmake("1.0.0", "build")

local lua = project("C")
local lake = project("c++")

lua:sourceDir("libs/lua/", ".c")
lua:includeDir("libs/lua")


lake:version("cxx17")

lake:sourceDir("src", ".cpp")

lake:includeDir("includes")
lake:link(lua)

lake:build("LakeBin.o")
