//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
#include "GError.h"
//===============================================
GObject::GObject(QObject* _parent) : QObject(_parent) {

}
//===============================================
GObject::~GObject() {

}
//===============================================
void GObject::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadXmlFile(GRES("xml", "app.xml"));
    m_dom->createXPath();
}
//===============================================
QString GObject::getItem(const QString& _code, const QString& _key, bool _isCData) const {
    return m_dom->getItem(_code, _key, _isCData);
}
//===============================================
QString GObject::getItem(const QString& _code, int _index, bool _isCData) const {
    return m_dom->getItem(_code, _index, _isCData);
}
//===============================================
QString GObject::getItem(const QString& _code, const QString& _key, int _index, bool _isCData) const {
    return m_dom->getItem(_code, _key, _index, _isCData);
}
//===============================================
QString GObject::getItem(const QString& _code, const QString& _category, const QString& _key, bool _isCData) const {
    return m_dom->getItem(_code, _category, _key, _isCData);
}
//===============================================
int GObject::countItem(const QString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
void GObject::addObj(const QString& _key, void* _obj) {
    m_objs[_key] = _obj;
}
//===============================================
void* GObject::getObj(const QString& _key, void* _defaultValue) const {
    void* lObj = m_objs.value(_key, _defaultValue);
    return lObj;
}
//===============================================
QString GObject::getKey(void* _obj, const QString& _defaultValue) const {
    QString lKey = m_objs.key(_obj, _defaultValue);
    return lKey;
}
//===============================================
bool GObject::hasErrors() const {
    return m_errors->hasErrors();
}
//===============================================
void GObject::clearErrors() {
    m_errors->clearErrors();
}
//===============================================
QVector<QString>& GObject::getErrors() {
    return m_errors->getErrors();
}
//===============================================
const QVector<QString>& GObject::getErrors() const {
    return m_errors->getErrors();
}
//===============================================
void GObject::runDefault(int _argc, char** _argv) {
    GERROR(eGERR, "Vous devez selectionner un module.");
}
//===============================================
