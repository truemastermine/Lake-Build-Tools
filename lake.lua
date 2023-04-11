-- lmake("1.0.0", "build")

local lua = project("C", "lua")
local lake = project("CPP", "lake")
print(lua == nil)
print(type(lua))
print(lake == nil)
print(type(lake))
-- print(lua.type)
-- print(type(lua.test))

-- lua:sourceDir("libs/lua/", ".c")
-- lua:includeDir("libs/lua")


-- -- lake:version("cxx17")

-- lake:source("src/main.cpp", "src/cpp.cpp")
-- lake:includeDir("includes")
-- -- lake:link(lua)

-- lake:build("LakeBin.o")

-- for _,v in ipairs(lake.gsrc) do
--     print(v)
-- end
-- print("-----------")
-- for _,v in ipairs(lua.gsrc) do
--     print(v)
-- end

