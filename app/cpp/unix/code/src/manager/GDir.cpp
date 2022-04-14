//===============================================
#include "GDir.h"
#include "GFormat.h"
//===============================================
GDir::GDir() : GObject() {

}
//===============================================
GDir::~GDir() {

}
//===============================================
std::vector<std::string> GDir::openDir(const std::string& _path, bool _full) const {
    struct dirent* lEntry = 0;
    DIR* lDir = opendir(_path.c_str());
    std::vector<std::string> lFiles;

    if(lDir != 0) {
        while((lEntry = readdir(lDir))) {
            std::string lFile = lEntry->d_name;
            if(_full) lFile = sformat("%s/%s", _path, lFile);
            lFiles.push_back(lFile);
        }
        closedir(lDir);
    }
    return lFiles;
}
//===============================================
