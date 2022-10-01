//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GObject::GObject() {
    m_isParent = true;
}
//===============================================
GObject::~GObject() {

}
//===============================================
void GObject::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GPATH("xml", "pad.xml"));
}
//===============================================
GString GObject::getItem(const GString& _code, const GString& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
GString GObject::getItem(const GString& _code, const GString& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
int GObject::countItem(const GString& _code) const {
    return m_dom->countItem(_code);
}
//===============================================
bool GObject::clearMap(std::vector<GObject*>& _map) {
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
GString GObject::serialize(const GString& _code) const {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
