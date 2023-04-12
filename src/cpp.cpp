#include "apis/cpp.h"

#include <filesystem>
#include <iostream>

#include "api.h"
namespace fs = std::filesystem;

namespace LBT {
namespace CPP {

static void createCPPProject(API::Project& pro, const std::string_view id) {
    pro.data = new CPPProject{.cpp = true, .id = id};
}

static void createCProject(API::Project& pro, const std::string_view id) {
    pro.data = new CPPProject{.cpp = false, .id = id};
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

static void buildLink(Link& lnk){
    auto pro = lnk.pro;
    std::string_view bin = pro->cpp ? "g++ " : "gcc ";
    std::string_view buildName = pro->id;

    // INCLUDES
    std::string incs;
    for (auto& incDir : pro->incDirs) {
        incs += " -I ";
        incs += incDir;
    }

    // SOURCE TO OBJ
    std::string srcs;
    for (auto& srcFile : pro->srcs){
        fs::path srcPath(srcFile);

        // FS Checks
        if (!(fs::exists(srcPath) && fs::is_regular_file(srcPath)))
            throw "Expected File Not Found: " + srcFile;
        if (fs::last_write_time(srcPath) < fs::last_write_time(srcPath)) continue;

        std::cout << bin << "-c " << srcFile << " -Wall -o " << API::buildDir //<< '/'
                  << srcPath.filename().replace_extension(".o").generic_string() << " " << incs
                  << '\n';
        srcs += ' ';
        srcs += API::buildDir;
        srcs += srcPath.filename().replace_extension(".o").generic_string();
    }

    std::cout << "ar rvs " << API::buildDir << buildName << ".a " << srcs << '\n';
}

static void buildProject(API::Project& p, std::string_view buildName) {
    auto pro = (CPPProject*)p.data;
    std::string_view bin = pro->cpp ? "g++ " : "gcc ";
    if (buildName.empty()) buildName = pro->id;
    // std::cout << pro.id << '\n';

    // LINKS
    std::string lnks;
    for (auto& link : pro->libs){
        buildLink(link);
        lnks += " ";
        lnks += API::buildDir;
        lnks += link.pro->id;
        lnks += ".a";
    }

    // INCLUDES
    std::string incs;
    for (auto& incDir : pro->incDirs) {
        incs += " -I ";
        incs += incDir;
    }

    // SOURCE OBJ FILES
    std::string srcs;
    for (auto& srcFile : pro->srcs) {
        fs::path srcPath(srcFile);

        // FS Checks
        if (!(fs::exists(srcPath) && fs::is_regular_file(srcPath)))
            throw "Expected File Not Found: " + srcFile;
        if (fs::last_write_time(srcPath) < fs::last_write_time(srcPath)) continue;

        std::cout << bin << "-c " << srcFile << " -Wall -o " << API::buildDir //<< '/'
                  << srcPath.filename().replace_extension(".o").generic_string() << " " << incs
                  << '\n';
        srcs += ' ';
        srcs += API::buildDir;
        srcs += srcPath.filename().replace_extension(".o").generic_string();
    }

    // FINAL COMPILATION
    std::cout << bin << srcs << lnks << " -o " << API::buildDir << "LAKE" <<'\n';
}

}  // namespace CPP

API::API CppAPI{.cProject = CPP::createCPPProject,
                .addSrc = CPP::addSource,
                .addIncDir = CPP::addIncDir,
                .linkPro = CPP::addLink,
                .build = CPP::buildProject};

API::API CAPI{.cProject = CPP::createCProject,
              .addSrc = CPP::addSource,
              .addIncDir = CPP::addIncDir,
              .linkPro = CPP::addLink,
              .build = CPP::buildProject};

}  // namespace LBT
