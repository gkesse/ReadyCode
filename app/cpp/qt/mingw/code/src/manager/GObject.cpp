//===============================================
#include "GObject.h"
//===============================================
GObject::GObject() {

}
//===============================================
GObject::~GObject() {

}
//===============================================
std::string GObject::getDataPath() const {
    std::string lPath = "C:/Users/Admin/Downloads/Programs/ReadyData/data/cpp";
    return lPath;
}
//===============================================
std::string GObject::getResourcePath(const std::string& _resource, const std::string& _filename) const {
    std::string lPath = _filename;
    if(_resource != "") {
        lPath = _resource + "/" + lPath;
    }
    if(getDataPath() != "") {
        lPath = getDataPath() + "/" + lPath;
    }
    return lPath;
}
//===============================================
std::string GObject::getXmlPath(const std::string& _filename) const {
    std::string lPath = getResourcePath("xml", _filename);
    return lPath;
}
//===============================================

