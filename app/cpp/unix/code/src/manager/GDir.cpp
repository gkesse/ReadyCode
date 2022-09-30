//===============================================
#include "GDir.h"
//===============================================
GDir::GDir() : GObject() {

}
//===============================================
GDir::~GDir() {

}
//===============================================
std::vector<GString> GDir::openDir(const GString& _path, bool _fullOn, bool _dotOn) const {
    struct dirent* lEntry = 0;
    DIR* lDir = opendir(_path.c_str());
    std::vector<GString> lFiles;

    if(lDir != 0) {
        while((lEntry = readdir(lDir))) {
            GString lFile = lEntry->d_name;
            if(!_dotOn && lFile == ".") continue;
            if(!_dotOn && lFile == "..") continue;
            if(_fullOn) lFile = GFORMAT("%s/%s", _path.c_str(), lFile.c_str());
            lFiles.push_back(lFile);
        }
        closedir(lDir);
    }
    std::sort(lFiles.begin(), lFiles.end());
    return lFiles;
}
//===============================================
