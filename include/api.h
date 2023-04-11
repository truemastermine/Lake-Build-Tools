#pragma once
#include <map>
#include <string_view>

#include "sol/sol.hpp"

namespace LBT {
namespace API {

void initSol(sol::state&);

struct Project {
    const std::string lang;
    void* data;
};

struct API {
    void (*cProject)(Project&, const sol::variadic_args&);

    // Source
    void (*addSrc)(Project&, const sol::variadic_args&);
    void (*addSrcDir)(Project&, const sol::variadic_args&);
};

extern std::map<std::string_view, API> apis;

};  // namespace API
}  // namespace LBT
