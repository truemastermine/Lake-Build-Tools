#include <filesystem>
#include <iostream>
#include <vector>
#include <map>

#include "apis/cpp.h"
#include "api.h"
#include "sol/sol.hpp"

namespace fs = std::filesystem;

void lmake() {}

int main() {
    sol::state lua;

    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::os,
                       sol::lib::package, sol::lib::string, sol::lib::table);

    // LBT::API::apis["CPP"];

    LBT::API::initSol(lua);

    // lua["project"] = LBT::project;

    // lua["API"] = lua.create_table();
    // lua["API"]["listDir"] = listDir;

    // auto res = lua.do_file("cpplua/init.lua", sol::load_mode::text);
    // std::cout << (int)res.status() << "\n";

    auto res = lua.do_file("lake.lua");
    std::cout << (int)res.status() << "\n";

    if ((bool)res.status()){
        sol::error err = res;
        std::cout << err.what() << '\n';
    }

    lua["execute"]();
}