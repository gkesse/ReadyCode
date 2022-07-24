//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GObject::GObject(QObject* _parent)
: QObject(_parent) {
    m_isParent = true;
}
//===============================================
GObject::~GObject() {

}
//===============================================
void GObject::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GRES("xml", "app.xml"));
}
//===============================================
QString GObject::getItem(const QString& _code, const QString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
QString GObject::getItem(const QString& _code, int _index) const {
    return m_dom->getItem(_code, _index);
}
//===============================================
QString GObject::getItem(const QString& _code, const QString& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
QString GObject::getItem(const QString& _code, const QString& _category, const QString& _key) const {
    return m_dom->getItem(_code, _category, _key);
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
void GObject::runDefault(int _argc, char** _argv) {
    GERROR_ADD(eGERR, "Vous devez selectionner un module.");
}
//===============================================
bool GObject::clearMap(QVector<GObject*>& _map) {
    for(int i = 0; i < (int)_map.size(); i++) {
        GObject* lObj = _map.at(i);
        delete lObj;
    }
    _map.clear();
    return true;
}
//===============================================
void GObject::setIsParent(bool _isParent) {
    m_isParent = _isParent;
}
//===============================================
GObject* GObject::clone() {return new GObject;}
QString GObject::serialize(const QString& _code) {return "";}
void GObject::deserialize(const QString& _data, const QString& _code) {}
//===============================================
