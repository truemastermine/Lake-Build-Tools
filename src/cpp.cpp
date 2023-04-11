#include "apis/cpp.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

namespace LBT {
namespace CPP {

// void addSource(sol::variadic_args){

// }

CPPProject createProject(std::string_view, sol::optional<std::string_view> id) {
    return createCPPProject(id.value_or(""));
}

void addSource(CPPProject& pro, sol::variadic_args args) {
    for (auto arg : args) {
        std::string_view sv = arg.as<std::string_view>();
        pro.srcs.emplace_back(sv);
    }
}

void addSourceDir(CPPProject& pro, std::string_view dir, std::string_view ext) {
    for (const auto& file : fs::recursive_directory_iterator(dir)) {
        auto path = file.path();
        if (path.extension() == ext) pro.srcs.emplace_back(path);
    }
}

void addIncludeDir(CPPProject& pro, sol::variadic_args args) {
    for (auto arg : args) {
        pro.incDirs.emplace_back(arg.as<std::string_view>());
    }
}

void build(CPPProject& pro, sol::optional<std::string_view> buildName){
    auto bn = buildName.value_or(pro.id);
    std::vector<std::string_view> cmds;
    for (auto& src : pro.srcs){
        cmds.emplace_back(std::string("g++ -I") + std::string(pro.incDirs[0])+"");\
        // std::cout << std::string("g++ -I") + std::string(pro.incDirs[0])+" "+src+ "-o outTemp -Wall -c" + "\n";
    }
}

void initSol(sol::state& lua) {
    lua["project"] = createProject;
    auto ud = lua.new_usertype<CPPProject>("CPPProject");
    ud["source"] = addSource;
    ud["sourceDir"] = addSourceDir;
    ud["includeDir"] = addIncludeDir;
    ud["build"] = build;
    ud["gsrc"] = &CPPProject::incDirs;
}

CPPProject createCPPProject(std::string_view id) { return CPPProject{}; }

}  // namespace CPP
}  // namespace LBT
