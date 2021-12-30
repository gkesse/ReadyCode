//===============================================
#include "GObject.h"
//===============================================
GObject* GObject::m_instance = 0;
//===============================================
GObject::GObject() {

}
//===============================================
GObject::~GObject() {

}
//===============================================
GObject* GObject::Instance() {
    if(m_instance == 0) {
        m_instance = new GObject;
    }
    return m_instance;
}
//===============================================
std::string GObject::getDataPath() const {
    std::string lPath = "C:/Users/Admin/Downloads/Programs/ReadyData/data";
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

