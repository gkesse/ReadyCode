//===============================================
#include "GCode.h"
#include "GObject.h"
#include "GLog.h"
#include "GPath.h"
//===============================================
GObject::GObject() {

}
//===============================================
GObject::~GObject() {

}
//===============================================
bool GObject::createDoms() {
    m_dom.reset(new GCode);
    m_dom->loadFile(GPATH("xml", "pad.xml"));
    return true;
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
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code) const {return "";}
bool GObject::deserialize(const GString& _data, const GString& _code) {return false;}
void GObject::print() const {}
//===============================================
