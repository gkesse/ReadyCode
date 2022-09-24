//===============================================
#include "GObject2.h"
#include "GLog.h"
#include "GCode2.h"
#include "GPath.h"
//===============================================
GObject2::GObject2() {

}
//===============================================
GObject2::~GObject2() {

}
//===============================================
bool GObject2::createDoms() {
    m_dom.reset(new GCode2);
    m_dom->loadFile(GRES("xml", "pad.xml"));
    return true;
}
//===============================================
void GObject2::clearMap(std::vector<GObject2*>& _map) const {
    for(int i = 0; i < (int)_map.size(); i++) {
        GObject2* lObj = _map.at(i);
        delete lObj;
    }
    _map.clear();
}
//===============================================
GObject2* GObject2::clone() const {return new GObject2;}
GString2 GObject2::serialize(const GString2& _code) const {return "";}
bool GObject2::deserialize(const GString2& _data, const GString2& _code) {return false;}
void GObject2::print() const {}
//===============================================
