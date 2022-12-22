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
    }
    return m_instance;
}
//===============================================
GString GPath::getDataPath() const {
    GEnv lEnv;
    GString lPath = lEnv.getEnv("GPROJECT_DATA");
    if(lPath == "") {
        GERROR_ADD(eGERR, "Erreur la methode (GPath::getDataPath) a echoue.");
        return "";
    }
    return lPath;
}
//===============================================
GString GPath::getResourcePath(const GString& _res, const GString& _filename) const {
    return getResourcePath(getDataPath(), _res, _filename);
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
