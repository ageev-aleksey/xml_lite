#include "filesystem/Directory.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sstream>


class DirectoryImpl {
public:
    DirectoryImpl() {
        mDirectory = nullptr;
    }

    bool open(const std::string &path) {
        mDirectory = opendir(path.c_str());
        if(mDirectory != NULL) {
            mPath = path;
            return true;
        }
        return false;
    }

    bool isOpen() {
        return mDirectory != NULL;
    }

    std::list<std::string> files() {
        if(!isOpen()) {
            throw std::runtime_error("directory was not opened");
        }
        dirent *entity = NULL;
        struct stat info;
        std::list<std::string> res;
        char pathName[PATH_MAX+1];
        while((entity = readdir(mDirectory)) != NULL) {
            if(strncmp(entity->d_name, ".", PATH_MAX) == 0) continue;
            if(strncmp(entity->d_name, "..", PATH_MAX) == 0) continue;
            strncpy(pathName, mPath.c_str(), PATH_MAX);
            strncat(pathName, "/", PATH_MAX);
            strncat(pathName, entity->d_name, PATH_MAX);

            if(lstat(pathName, &info) == 0) {
                if(S_ISREG(info.st_mode)) {
                    res.emplace_back(entity->d_name);
                } else if(S_ISLNK(info.st_mode)) {
                    char targetName[PATH_MAX + 1];
                    if(readlink(pathName, targetName, PATH_MAX) != -1) {
                        //TODO нужна ли приоверка на тип прочитанной сущности
                        res.emplace_back(targetName);
                    } else {
                        std::stringstream msg;
                        msg << "Error get simlink (" << pathName << ") info";
                        throw std::runtime_error(msg.str());
                    }
                }
            } else {
                std::stringstream msg;
                msg << "Error get filesystem entity(" << pathName << ") info";
                throw std::runtime_error(msg.str());
            }
        }

        return res;

    }

private:
    DIR *mDirectory;
    std::string mPath;
};



Directory::Directory() : pimpl(new DirectoryImpl) {
}

Directory::Directory(const Directory &dir) {
    delete  pimpl;
    pimpl = new DirectoryImpl(*dir.pimpl);
}

Directory::~Directory() {
        delete  pimpl;
}

bool Directory::open(std::string path) {
    return  pimpl->open(path);
}

std::list<std::string> Directory::files() {
    return pimpl->files();
}



