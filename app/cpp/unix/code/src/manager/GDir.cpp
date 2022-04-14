//===============================================
#include "GDir.h"
//===============================================
GDir::GDir() : GObject() {

}
//===============================================
GDir::~GDir() {

}
//===============================================
std::vector<std::string> GDir::openDir(const std::string& _path) const {
    struct dirent* lEntry = 0;
    DIR* lDir = opendir(_path.c_str());
    std::vector<std::string> lFiles;

    if(lDir != 0) {
        while((lEntry = readdir(lDir))) {
            lFiles.push_back(lEntry->d_name);
        }
        closedir(lDir);
    }
    return lFiles;
}
//===============================================
