#pragma once
#include <string_view>
#include <optional>
#include <vector>
#include "sol/sol.hpp"

namespace LBT {

// struct Project{};

namespace CPP {

struct CPPProject;

// enum class LinkType : char {
//     DEFAULT = 0,
//     STATIC,
//     SHARED
// };

struct Link {
    CPPProject* pro;
    unsigned char type;
};

struct CPPProject {
    std::string_view id;
    bool cpp = true;
    std::vector<Link> libs;
    std::vector<std::string> srcs;
    std::vector<std::string> incDirs;
};

}  // namespace CPP
}  // namespace LBT
