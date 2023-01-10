//===============================================
#include "GPath.h"
#include "GEnv.h"
//===============================================
GPath* GPath::m_instance = 0;
//===============================================
GPath::GPath() : GObject() {

}
//===============================================
GPath::~GPath() {

}
//===============================================
GPath* GPath::Instance() {
    if(m_instance == 0) {
        m_instance = new GPath;
        m_instance->initPath();
    }
    return m_instance;
}
//===============================================
void GPath::initPath() {
    GEnv lEnv;
    m_dataPath = lEnv.getEnv("GPROJECT_DATA");
}
//===============================================
GString GPath::getResourcePath(const GString& _res, const GString& _filename) const {
    return getResourcePath(m_dataPath, _res, _filename);
}
//===============================================
GString GPath::getResourcePath(const GString& _root, const GString& _res, const GString& _filename) const {
    GString lPath = "";
    if(_root != "") {
        lPath += GFORMAT("%s", _root.c_str());
    }
    if(_res != "") {
        if(lPath != "") {
            lPath += GFORMAT("/%s", _res.c_str());
        }
        else {
            lPath += GFORMAT("%s", _res.c_str());
        }
    }
    if(_filename != "") {
        if(lPath != "") {
            lPath += GFORMAT("/%s", _filename.c_str());
        }
        else {
            lPath += GFORMAT("%s", _filename.c_str());
        }
    }
    return lPath;
}
//===============================================
