//===============================================
#include "GDialog.h"
#include "GLog.h"
#include "GXml.h"
//===============================================
GDialog::GDialog(QWidget* _parent) :
QDialog(_parent) {

}
//===============================================
GDialog::~GDialog() {

}
//===============================================
QString GDialog::getItem(const QString& _code, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_code).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QString GDialog::getItem(const QString& _code, const QString& _data, int _i) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/map/data[position()=%2]/%3").arg(_code).arg(_i + 1).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
int GDialog::countItem(const QString& _code) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/map/data").arg(_code));
    int lData = m_dom->countXPath();
    return lData;
}
//===============================================
void GDialog::addObject(QObject* _object, const QString& _key) {
    if(_key != "") {
        m_objectMap[_object] = _key;
    }
}
//===============================================
QObject* GDialog::getObject(const QString& _key) {
    QObject* lObject = m_objectMap.key(_key, 0);
    if(lObject == 0) {
        GERROR(eGERR, QString(""
                "Erreur la cle n'existe pas.\n"
                "cle..........: (%1)\n").arg(_key));
    }
    GERROR_SHOWG(eGERR);
    return lObject;
}
//===============================================
QString GDialog::getObject(QObject* _key, const QString& _defaultValue) {
    return m_objectMap.value(_key, _defaultValue);
}
//===============================================
void GDialog::onErrorKey(const QString& _key) {
    GERROR(eGERR, QString(""
            "Erreur la cle n'existe pas.\n"
            "cle..........: (%1)\n"
            "").arg(_key)
    );
}
//===============================================
