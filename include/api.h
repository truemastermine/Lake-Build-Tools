#pragma once
#include <map>
#include <string_view>

#include "sol/sol.hpp"

namespace LBT {
namespace API {

void initSol(sol::state&);

enum class LinkType : unsigned char {
    DEFAULT = 0,
    STATIC,
    SHARED
};

struct Project {
    const std::string lang;
    void* data;
};

struct API {
    void (*cProject)(Project&, const std::string_view);

    // Source
    void (*addSrc)(Project&, const std::string_view);
    void (*addIncDir)(Project&, const std::string_view);
    void (*linkPro)(Project& Self, Project& T, LinkType);
    void (*build)(Project&, const std::string_view);
};

extern std::map<std::string_view, API> apis;

};  // namespace API
}  // namespace LBT
