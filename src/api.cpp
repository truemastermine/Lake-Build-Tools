#include "api.h"

#include <filesystem>
#include <iostream>

#include "sol/sol.hpp"
namespace fs = std::filesystem;

namespace LBT {
extern API::API CppAPI;
extern API::API CAPI;

namespace API {

std::map<std::string_view, API> apis;

sol::optional<Project> createProject(std::string_view lang, std::optional<std::string_view> id) {
    if (apis.find(lang) == apis.end()) return sol::optional<Project>();

    Project pro{std::string(lang), nullptr};
    apis[lang].cProject(pro, id.value_or(""));
    return pro;
}

static void addSource(Project& pro, const sol::variadic_args args) {
    auto addSrc = apis[pro.lang].addSrc;
    for (auto& arg : args) {
        addSrc(pro, arg.get<std::string_view>());
    }
}

 static void addSrcDir(Project& pro, std::string_view ext, const sol::variadic_args args) {
    std::vector<fs::path> files;
    auto addSrc = apis[pro.lang].addSrc;

    for (auto& dir : args) {
        for (auto& f : fs::recursive_directory_iterator(dir.get<std::string_view>())) {
            auto& p = f.path();
            if (p.extension() != ext) continue;

            addSrc(pro, p.generic_string());
            // files.emplace_back(p);
        }
    }

    // apis[pro.lang].addSrcDir(pro, args);
}

static void addIncDir(Project& pro, const sol::variadic_args args) {
    auto addInc = apis[pro.lang].addIncDir;

    for (auto& arg : args) {
        addInc(pro, arg.get<std::string_view>());
    }
}

static void addLink(Project& pro, const sol::optional<std::variant<std::string_view, int>> t,
             const sol::variadic_args args) {
    LinkType lt = LinkType::DEFAULT;

    if (t.has_value()) {
        auto var = t.value();
        if (var.index()) {
            lt = (LinkType)std::get<1>(var);
        } else {
            auto val = std::get<0>(var);
            if (val == "STATIC" || val == "static")
                lt = LinkType::STATIC;
            else if (val == "DYNAMIC" || val == "dynamic" || val == "SHARED" || val == "shared")
                lt = LinkType::SHARED;
            else
                throw "Unknown Link Type";
        }
    }

    auto addLink = apis[pro.lang].linkPro;
    for (auto& arg : args) {
        auto target = arg.get<Project>();
        if (pro.data == target.data) throw "You can't link a project to itself!";
        addLink(pro, target, lt);
    }
}

static void buildProject(Project& pro, sol::optional<std::string_view> buildName) {
    auto bn = buildName.value_or("");

    apis[pro.lang].build(pro, bn);
}

void initSol(sol::state& lua) {
    lua["project"] = LBT::API::createProject;

    auto ut = lua.new_usertype<Project>("ProjectMeta");
    ut["source"] = &addSource;
    ut["sourceDir"] = &addSrcDir;
    ut["includeDir"] = &addIncDir;
    ut["link"] = &addLink;
    ut["build"] = &buildProject;

    // APIS

    apis["CPP"] = CppAPI;
    apis["C"] = CAPI;
}

}  // namespace API
}  // namespace LBT