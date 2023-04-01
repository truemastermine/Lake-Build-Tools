-- TODO: add_custom_command, cmake_path, file, find_..., add_compile_options
includeg() -- Protect when included
lmake("1.0.0", "build") -- (required version, buildDir) major.minor.patch.indev

local lib = project("C++") -- (language)

lib:source("libs/lib/main.cpp", "libs/lib/optional.cpp") -- (source files...)
lib:sourceDir("libs/lib/src", ".cpp") -- (dir, extension)
lib:includeDir("libs/lib/includes") -- (include dir...)
lib:define("STATIC_LIB") -- (key, value)

local myPro = project("cxx")
myPro:version("cxx17") -- (language version)

eval("echo 'Hello, World!'") -- (cmd, continueOnErr)

myPro:sourceDir("src", ".cpp")
myPro:includeDir("includes")
myPro:link("static", lib) -- (type?, project...)

myPro:testDir("test")
myPro:buildTest()

myPro:build("main") -- (filename, {win32 = false, macosx_bundle = false})
-- message("DONE") -- alias of print
message("error", "Print: {}", "Hello World!") -- (mode, fstring, ...) print = message(nil, ...)

store("inctes", "include test", true, false) -- (id, name, default, override)
if get("inctes") then
    include("test", true) -- (path, optional) execute the following lmake file
end
