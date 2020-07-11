#include "filesystem/Directory.h"
#include <iostream>

int main() {
    Directory cwd;
    if(!cwd.open(".")) {
        std::cout << "error opening dir" << std::endl;
        return -1;
    }
    auto files = cwd.files();
    for(const auto &el : files) {
        std::cout << el << std::endl;
    }

    return 0;
}