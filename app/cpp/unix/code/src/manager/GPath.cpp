//===============================================
#include "GPath.h"
#include "GFormat.h"
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
std::string GPath::getDataPath() const {
	std::string lPath = getenv("GPROJECT_DATA");
	return lPath;
}
//===============================================
std::string GPath::getResourcePath(const std::string& _res, const std::string& _filename) const {
	std::string lPath = "";
	if(getDataPath() != "") {
		lPath += GFORMAT->sformat("%s", getDataPath().c_str());
	}
	if(_res != "") {
		if(lPath != "") {
			lPath += GFORMAT->sformat("/%s", _res.c_str());
		}
		else {
			lPath += GFORMAT->sformat("%s", _res.c_str());
		}
	}
	if(_filename != "") {
		if(lPath != "") {
			lPath += GFORMAT->sformat("/%s", _filename.c_str());
		}
		else {
			lPath += GFORMAT->sformat("%s", _filename.c_str());
		}
	}
	return lPath;
}
//===============================================
