//===============================================
#include "GPath2.h"
#include "GEnv2.h"
#include "GLog2.h"
//===============================================
GPath2* GPath2::m_instance = 0;
//===============================================
GPath2::GPath2(QObject* _parent)
: GObject2(_parent) {

}
//===============================================
GPath2::~GPath2() {

}
//===============================================
GPath2* GPath2::Instance() {
    if(m_instance == 0) {
        m_instance = new GPath2;
    }
    return m_instance;
}
//===============================================
GString GPath2::getDataPath() const {
    GEnv2 lEnv;
    GString lPath = lEnv.getEnv("GPROJECT_DATA");
    if(lPath == "") {GERROR_ADD2(eGERR, "Le chemin des données n'est pas définie."); return "";}
    return lPath;
}
//===============================================
GString GPath2::getResourcePath(const GString& _res, const GString& _filename) const {
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
