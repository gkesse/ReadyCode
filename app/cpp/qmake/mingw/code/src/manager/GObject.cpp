//===============================================
#include "GObject.h"
#include "GXml.h"
//===============================================
GObject::GObject(QObject* _parent) : QObject(_parent) {

}
//===============================================
GObject::~GObject() {

}
//===============================================
QString GObject::getItem(const QString& _key, const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='%1']/%2").arg(_key).arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
QSharedPointer<GError>& GObject::getErrors() {
    return m_errors;
}
//===============================================
