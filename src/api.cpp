#include "api.h"

#include "sol/sol.hpp"

namespace LBT {
namespace API {

std::map<std::string_view, API> apis;

sol::optional<Project> createProject(std::string_view lang, sol::variadic_args args) {
    if (apis.find(lang) == apis.end()) return sol::optional<Project>();

    return Project{};
}

void addSource(Project& pro, const sol::variadic_args args){
    apis[pro.lang].addSrc(pro, args);
}

}  // namespace API
}  // namespace LBT