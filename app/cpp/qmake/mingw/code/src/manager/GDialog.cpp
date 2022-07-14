//===============================================
#include "GDialog.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GDialog::GDialog(QWidget* _parent) :
QDialog(_parent) {

}
//===============================================
GDialog::~GDialog() {

}
//===============================================
void GDialog::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadXmlFile(GRES("xml", "app.xml"));
    m_dom->createXPath();
}
//===============================================
QString GDialog::getItem(const QString& _code, const QString& _key, bool _isCData) const {
    return m_dom->getItem(_code, _key, _isCData);
}
//===============================================
QString GDialog::getItem(const QString& _code, int _index, bool _isCData) const {
    return m_dom->getItem(_code, _index, _isCData);
}
//===============================================
QString GDialog::getItem(const QString& _code, const QString& _key, int _index, bool _isCData) const {
    return m_dom->getItem(_code, _key, _index, _isCData);
}
//===============================================
QString GDialog::getItem(const QString& _code, const QString& _category, const QString& _key, bool _isCData) const {
    return m_dom->getItem(_code, _category, _key, _isCData);
}
//===============================================
int GDialog::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
void GDialog::addObj(const QString& _key, void* _obj) {
    m_objs[_key] = _obj;
}
//===============================================
void* GDialog::getObj(const QString& _key, void* _defaultValue) const {
    void* lObj = m_objs.value(_key, _defaultValue);
    return lObj;
}
//===============================================
QString GDialog::getKey(void* _obj, const QString& _defaultValue) const {
    QString lKey = m_objs.key(_obj, _defaultValue);
    return lKey;
}
//===============================================
void GDialog::onErrorKey(const QString& _key) {
    GERROR(eGERR, QString(""
            "Erreur la cle (%1) n'existe pas.\n"
            "").arg(_key)
    );
}
//===============================================
