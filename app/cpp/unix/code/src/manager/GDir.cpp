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
std::vector<std::string> GDir::openDir(const std::string& _path, bool _fullOn, bool _dotOn) const {
    struct dirent* lEntry = 0;
    DIR* lDir = opendir(_path.c_str());
    std::vector<std::string> lFiles;

    if(lDir != 0) {
        while((lEntry = readdir(lDir))) {
            std::string lFile = lEntry->d_name;
            if(!_dotOn && lFile == ".") continue;
            if(!_dotOn && lFile == "..") continue;
            if(_fullOn) lFile = sformat("%s/%s", _path.c_str(), lFile.c_str());
            lFiles.push_back(lFile);
        }
        closedir(lDir);
    }
    std::sort(lFiles.begin(), lFiles.end());
    return lFiles;
}
//===============================================
