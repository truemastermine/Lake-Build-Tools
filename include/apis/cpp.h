#pragma once
#include <string_view>
#include <optional>
#include <vector>
#include "sol/sol.hpp"

namespace LBT {

// struct Project{};

namespace CPP {

struct CPPProject;

enum class LinkType : char {
    DEFAULT = 0,
    STATIC,
    SHARED
};

struct Links {
    CPPProject* pro;
    LinkType type;
};

struct CPPProject {
    std::string_view id;
    bool cpp = true;
    std::vector<Links> libs;
    std::vector<std::string> srcs;
    std::vector<std::string> incDirs;
};

}  // namespace CPP
}  // namespace LBT
