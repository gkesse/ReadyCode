//===============================================
#include "GObject.h"
#include "GPath.h"
#include "GCode.h"
//===============================================
GObject::GObject(const GString& _codeName) {
    m_codeName = _codeName;
    m_isOnlyObjectCopied = false;
}
//===============================================
GObject::~GObject() {

}
//===============================================
bool GObject::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GPATH("xml", "app.xml"));
    return true;
}
//===============================================
void GObject::clearMap() {
    clearMap(m_map);
}
//===============================================
void GObject::clearMap(std::vector<GObject*>& _map) const {
    for(int i = 0; i < (int)_map.size(); i++) {
        GObject* lObj = _map.at(i);
        delete lObj;
    }
    _map.clear();
}
//===============================================
int GObject::size() const {
    return m_map.size();
}
//===============================================
GObject* GObject::at(int _index) {
    if(_index >= 0 && _index < (int)m_map.size()) {
        return m_map.at(_index);
    }
    return 0;
}
//===============================================
void GObject::add(GObject* _obj) {
    m_map.push_back(_obj);
}
//===============================================
void GObject::print() {
    printf("%s\n", serialize(getCodeName()).c_str());
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code) {return "";}
bool GObject::deserialize(const GString& _data, const GString& _code) {return false;}
GString GObject::getCodeName() const {return m_codeName;}
bool GObject::isOnlyObjectCopied() const {return m_isOnlyObjectCopied;}
void GObject::setOnlyObjectCopied() {m_isOnlyObjectCopied = true;}
void GObject::resetOnlyObjectCopied() {m_isOnlyObjectCopied = false;}
//===============================================
