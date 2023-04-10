#include <filesystem>
#include <iostream>
#include <vector>

#include "apis/cpp.h"
#include "sol/sol.hpp"

namespace fs = std::filesystem;

void lmake() {}

namespace LBT {

void* project(std::string_view lang, sol::optional<std::string_view> id) {
    // if (lang == "C") return CPP::createCProject(id.value_or(""));
    if (lang == "CPP") return CPP::createCPPProject(id.value_or(""));

    return nullptr;
}
}  // namespace LBT
std::vector<std::string> listDir(std::string_view dir, std::string_view ext) {
    std::vector<std::string> res;
    for (const auto& file : fs::recursive_directory_iterator(dir)) {
        // std::cout << file.path() << '\n';
        auto path = file.path();
        if (path.extension() == ext) res.push_back(path);
    }
    return res;
}

int main() {
    sol::state lua;

    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::os,
                       sol::lib::package, sol::lib::string, sol::lib::table);

    lua["project"] = LBT::project;

    // lua["API"] = lua.create_table();
    // lua["API"]["listDir"] = listDir;

    // auto res = lua.do_file("cpplua/init.lua", sol::load_mode::text);
    // std::cout << (int)res.status() << "\n";

    auto res = lua.do_file("lake.lua");
    std::cout << (int)res.status() << "\n";

    lua["execute"]();
}