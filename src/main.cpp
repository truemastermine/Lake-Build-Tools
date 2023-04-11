#include <filesystem>
#include <iostream>
#include <vector>
#include <map>

#include "apis/cpp.h"
#include "sol/sol.hpp"

namespace fs = std::filesystem;

void lmake() {}

int main() {
    sol::state lua;

    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::os,
                       sol::lib::package, sol::lib::string, sol::lib::table);

    LBT::apis["CPP"] = 10;

    // LBT::CPP::initSol(lua);
    lua["project"] = LBT::createProject;

    // lua["project"] = LBT::project;

    // lua["API"] = lua.create_table();
    // lua["API"]["listDir"] = listDir;

    // auto res = lua.do_file("cpplua/init.lua", sol::load_mode::text);
    // std::cout << (int)res.status() << "\n";

    auto res = lua.do_file("lake.lua");
    std::cout << (int)res.status() << "\n";

    lua["execute"]();
}