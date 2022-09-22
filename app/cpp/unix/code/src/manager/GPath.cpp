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
std::string GPath::getPath() const {
    GEnv lEnv;
    std::string lPath = lEnv.getEnv("GPROJECT_DATA");
    if(lPath == "") {
        GERROR_ADD(eGERR, "Erreur la methode (GPath::getDataPath) a echoue.");
        return "";
    }
    return lPath;
}
//===============================================
std::string GPath::getResourcePath(const std::string& _res, const std::string& _filename) const {
    std::string lPath = "";
    if(getPath() != "") {
        lPath += sformat("%s", getPath().c_str());
    }
    if(_res != "") {
        if(lPath != "") {
            lPath += sformat("/%s", _res.c_str());
        }
        else {
            lPath += sformat("%s", _res.c_str());
        }
    }
    if(_filename != "") {
        if(lPath != "") {
            lPath += sformat("/%s", _filename.c_str());
        }
        else {
            lPath += sformat("%s", _filename.c_str());
        }
    }
    return lPath;
}
//===============================================
