#include <iostream>
#include <filesystem>
#include <vector>

#include "sol/sol.hpp"

namespace fs = std::filesystem;

void lmake(){}
void project(){}
std::vector<std::string> listDir(std::string_view dir, std::string_view ext){
    std::vector<std::string> res;
    for (const auto& file : fs::recursive_directory_iterator(dir)){
        std::cout << file.path() << '\n';
    }
    return res;
}

int main() { 
    sol::state lua;
    listDir("/extra", "");

}