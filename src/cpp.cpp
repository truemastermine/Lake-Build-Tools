#include "apis/cpp.h"

#include <filesystem>
#include <iostream>

#include "api.h"
namespace fs = std::filesystem;

namespace LBT {
namespace CPP {

static void createCPPProject(API::Project& pro, const sol::variadic_args& args) {
    pro.data = new CPPProject();
}

static void addSource(API::Project& p, const std::string_view src) {
    CPPProject pro = *(CPPProject*)p.data;
    pro.srcs.emplace_back(src);
}

static void addIncDir(API::Project& p, const std::string_view dir) {
    CPPProject pro = *(CPPProject*)p.data;
    pro.incDirs.emplace_back(dir);
}

static void addLink(API::Project& pro, API::Project& target, API::LinkType ty) {
    
}

// void build(CPPProject& pro, sol::optional<std::string_view> buildName){
//     auto bn = buildName.value_or(pro.id);
//     std::vector<std::string_view> cmds;
//     for (auto& src : pro.srcs){
//         cmds.emplace_back(std::string("g++ -I") + std::string(pro.incDirs[0])+"");\
//         // std::cout << std::string("g++ -I") + std::string(pro.incDirs[0])+" "+src+ "-o outTemp
//         -Wall -c" + "\n";
//     }
// }

// void initSol(sol::state& lua) {
//     lua["project"] = createProject;
//     auto ud = lua.new_usertype<CPPProject>("CPPProject");
//     ud["source"] = addSource;
//     ud["sourceDir"] = addSourceDir;
//     ud["includeDir"] = addIncludeDir;
//     ud["build"] = build;
//     ud["gsrc"] = &CPPProject::incDirs;
// }

// CPPProject createCPPProject(std::string_view id) { return CPPProject{}; }

}  // namespace CPP

API::API CppAPI{.cProject = CPP::createCPPProject,
                .addSrc = CPP::addSource,
                .addIncDir = CPP::addIncDir,
                .linkPro = CPP::addLink};

API::API CAPI{.cProject = CPP::createCPPProject,
              .addSrc = CPP::addSource,
              .addIncDir = CPP::addIncDir,
              .linkPro = CPP::addLink};

}  // namespace LBT
