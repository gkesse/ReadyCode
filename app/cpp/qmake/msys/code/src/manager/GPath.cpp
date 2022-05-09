//===============================================
#include "GPath.h"
//===============================================
GPath* GPath::m_instance = 0;
//===============================================
GPath::GPath(QObject* _parent) :
GObject(_parent) {

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
QString GPath::getDataPath() const {
	QString lPath = getenv("GPROJECT_DATA");
	return lPath;
}
//===============================================
QString GPath::getResourcePath(const QString& _res, const QString& _filename) const {
	QString lPath = "";
	if(getDataPath() != "") {
		lPath += QString("%1").arg(getDataPath());
	}
	if(_res != "") {
		if(lPath != "") {
			lPath += QString("/%1").arg(_res);
		}
		else {
			lPath += QString("%1").arg(_res);
		}
	}
	if(_filename != "") {
		if(lPath != "") {
			lPath += QString("/%1").arg(_filename);
		}
		else {
			lPath += QString("%1").arg(_filename);
		}
	}
	return lPath;
}
//===============================================
