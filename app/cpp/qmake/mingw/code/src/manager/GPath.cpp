//===============================================
#include "GPath.h"
#include "GLog.h"
#include "GEnv.h"
//===============================================
GPath* GPath::m_instance = 0;
//===============================================
GPath::GPath()
: GObject() {

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
    if(lPath == "") {GERROR_ADD(eGERR, "Le chemin des données n'est pas définie."); return "";}
    return lPath;
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
