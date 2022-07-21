//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GFormat.h"
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
    m_dom->loadFile(GRES("xml", "pad.xml"));
}
//===============================================
std::string GObject::getItem(const std::string& _code, const std::string& _key) const {
    return m_dom->getItem(_code, _key);
}
//===============================================
std::string GObject::getItem(const std::string& _code, const std::string& _key, int _index) const {
    return m_dom->getItem(_code, _key, _index);
}
//===============================================
int GObject::countItem(const std::string& _code) const {
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
std::string GObject::serialize(const std::string& _code) const {return "";}
void GObject::deserialize(const std::string& _data, const std::string& _code) {}
//===============================================
