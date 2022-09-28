//===============================================
#include "GLocale.h"
#include "GCode.h"
//===============================================
GLocale::GLocale()
: GObject() {
    createDoms();
    deserializeDom();
}
//===============================================
GLocale::~GLocale() {

}
//===============================================
void GLocale::deserialize(const QString& _data, const QString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_encoding = getItem(_code, "lang");
}
//===============================================
void GLocale::deserializeDom(const QString& _code) {
    QString lData = m_dom->toString();
    deserialize(lData, _code);
}
//===============================================
void GLocale::initLocale() {
    setlocale(LC_ALL, m_encoding.toStdString().c_str());
}
//===============================================
