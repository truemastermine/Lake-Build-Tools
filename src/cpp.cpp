#include "apis/cpp.h"

#include <filesystem>
#include <iostream>

#include "api.h"
namespace fs = std::filesystem;

namespace LBT {
namespace CPP {

static void createCPPProject(API::Project& pro, const sol::variadic_args& args) {
    pro.data = new CPPProject{.id="Test"};
}

static void addSource(API::Project& p, const std::string_view src) {
    auto pro = (CPPProject*)p.data;
    pro->srcs.emplace_back(src);
}

static void addIncDir(API::Project& p, const std::string_view dir) {
    auto pro = (CPPProject*)p.data;
    pro->incDirs.emplace_back(dir);
}

static void addLink(API::Project& p, API::Project& target, API::LinkType ty) {
    if (target.lang != "C" && target.lang != "CPP")
        throw "You tried to link a unsupported language to this project!";

    auto pro = (CPPProject*)p.data;
    auto targ = (CPPProject*)target.data;

    pro->libs.emplace_back(Link{.pro = targ, .type = (unsigned char)ty});
}

static void buildProject(API::Project& p, std::string_view buildName) {
    auto pro = (CPPProject*)p.data;
    if (buildName.empty()) buildName = pro->id;
    // std::cout << pro.id << '\n';

    // INCLUDES
    std::string incs;
    for (auto& incDir : pro->incDirs) {
        incs += " -I ";
        incs += incDir;
    }

    // SOURCES
    for (auto& srcFile : pro->srcs) {
        std::cout << "g++ -c " << srcFile << " -o " << buildName << incs << '\n';
    }
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

// CPPProject createCPPProject(std::string_view id) { return CPPProject{}; }

}  // namespace CPP

API::API CppAPI{.cProject = CPP::createCPPProject,
                .addSrc = CPP::addSource,
                .addIncDir = CPP::addIncDir,
                .linkPro = CPP::addLink,
                .build = CPP::buildProject};

API::API CAPI{.cProject = CPP::createCPPProject,
              .addSrc = CPP::addSource,
              .addIncDir = CPP::addIncDir,
              .linkPro = CPP::addLink,
              .build = CPP::buildProject};

}  // namespace LBT
