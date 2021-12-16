//===============================================
#include "GQtResource.h"
#include "GQtLog.h"
//===============================================
GQtResource* GQtResource::m_instance = 0;
//===============================================
GQtResource::GQtResource(QObject* _parent) :
                        GQtObject(_parent) {

}
//===============================================
GQtResource::~GQtResource() {

}
//===============================================
GQtResource* GQtResource::Instance() {
    if(m_instance == 0) {
        m_instance = new GQtResource;
    }
    return m_instance;
}
//===============================================
QString GQtResource::getResPath(const QString& _dataPath, const QString& _resPath, const QString& _filename) {
    QString lPath = _filename;
    if(_resPath != "") {
        lPath = QString("%1/%2").arg(_resPath).arg(lPath);
    }
    if(_dataPath != "") {
        lPath = QString("%1/%2").arg(_dataPath).arg(lPath);
    }
    return lPath;
}
//===============================================
QString GQtResource::getXmlPath(const QString& _filename) {
    QString lPath = getResPath(getDataPath(), "xml", _filename);
    return lPath;
}
//===============================================
