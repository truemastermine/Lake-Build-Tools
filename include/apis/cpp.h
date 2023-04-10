#pragma once
#include <string_view>
#include <optional>
#include <vector>

namespace LBT {
namespace CPP {

void* createCPPProject(std::string_view id);

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
    std::vector<std::string_view> srcs;
    std::vector<std::string_view> incDirs;
};

}  // namespace CPP
}  // namespace LBT
