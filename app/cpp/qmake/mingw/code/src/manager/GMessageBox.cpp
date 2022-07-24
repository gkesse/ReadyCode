//===============================================
#include "GMessageBox.h"
#include "GTitleBarMsg.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GMessageBox::GMessageBox(QWidget* _parent) :
QMessageBox(_parent) {
    new GTitleBarMsg(this);
}
//===============================================
GMessageBox::~GMessageBox() {

}
//===============================================
void GMessageBox::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GRES("xml", "app.xml"));
}
//===============================================
QString GMessageBox::getItem(const QString& _code, const QString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
QString GMessageBox::getItem(const QString& _code, int _index) const {
    return m_dom->getItem(_code, _index);
}
//===============================================
QString GMessageBox::getItem(const QString& _code, const QString& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
QString GMessageBox::getItem(const QString& _code, const QString& _category, const QString& _key) const {
    return m_dom->getItem(_code, _category, _key);
}
//===============================================
int GMessageBox::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
void GMessageBox::addObj(const QString& _key, void* _obj) {
    m_objs[_key] = _obj;
}
//===============================================
void* GMessageBox::getObj(const QString& _key, void* _defaultValue) const {
    void* lObj = m_objs.value(_key, _defaultValue);
    return lObj;
}
//===============================================
QString GMessageBox::getKey(void* _obj, const QString& _defaultValue) const {
    QString lKey = m_objs.key(_obj, _defaultValue);
    return lKey;
}
//===============================================
void GMessageBox::onErrorKey(const QString& _key) {
    GERROR_ADD(eGERR, QString(""
            "Erreur la cle (%1) n'existe pas.\n"
            "").arg(_key)
    );
}
//===============================================
