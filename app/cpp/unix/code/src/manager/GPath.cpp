//===============================================
#include "GPath.h"
#include "GLog.h"
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
GString GPath::getPath() const {
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
    GString lPath = "";
    if(getPath() != "") {
        lPath += GFORMAT("%s", getPath().c_str());
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
