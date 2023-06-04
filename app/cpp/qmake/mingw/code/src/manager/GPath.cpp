//===============================================
#include "GPath.h"
#include "GEnv.h"
//===============================================
GPath* GPath::m_instance = 0;
//===============================================
GPath::GPath()
: GObject() {
    initPath();
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
void GPath::initPath() {
    m_dataPath = GEnv().getDataPath();
}
//===============================================
GString GPath::getDataPath() const {
    return m_dataPath;
}
//===============================================
GString GPath::getResourcePath(const GString& _res, const GString& _filename) const {
    GString lPath = "";
    if(getDataPath() != "") {
        lPath += GFORMAT("%s", getDataPath().c_str());
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
