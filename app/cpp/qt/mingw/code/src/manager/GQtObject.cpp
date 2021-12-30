//===============================================
#include "GQtObject.h"
#include "GQtLog.h"
//===============================================
GQtObject* GQtObject::m_instance = 0;
//===============================================
GQtObject::GQtObject(QObject* _parent) :
QObject(_parent) {

}
//===============================================
GQtObject::~GQtObject() {

}
//===============================================
GQtObject* GQtObject::Instance() {
    if(m_instance == 0) {
        m_instance = new GQtObject;
    }
    return m_instance;
}
//===============================================
QString GQtObject::getDataPath() {
    QString lPath = "C:/Users/Admin/Downloads/Programs/ReadyData/data";
    return lPath;
}
//===============================================
QString GQtObject::getResourcePath(const QString& _resource, const QString& _filename) {
    QString lPath = _filename;
    if(_resource != "") {
        lPath = QString("%1/%2").arg(_resource).arg(lPath);
    }
    if(getDataPath() != "") {
        lPath = QString("%1/%2").arg(getDataPath()).arg(lPath);
    }
    bool lExist = QFileInfo().exists(lPath);
    if(!lExist) {
        GQTLOG->addError(QString("Erreur la methode (getResourcePath) a echoue "
                "sur la ressource (%1) et le fichier (%2)").arg(_resource).arg(_filename));
        return "";
    }
    return lPath;
}
//===============================================
