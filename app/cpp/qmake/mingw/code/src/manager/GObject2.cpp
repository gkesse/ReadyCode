//===============================================
#include "GObject2.h"
#include "GCode2.h"
#include "GPath2.h"
//===============================================
GObject2::GObject2(QObject* _parent)
: QObject(_parent) {

}
//===============================================
GObject2::~GObject2() {

}
//===============================================
bool GObject2::createDoms() {
    m_dom.reset(new GCode2);
    m_dom->loadFile(GPATH("xml", "app.xml"));
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
void GObject2::print() const {
    printf("%s\n", serialize().c_str());
}
//===============================================
GObject2* GObject2::clone() const {return new GObject2;}
GString GObject2::serialize(const GString& _code) const {return "";}
bool GObject2::deserialize(const GString& _data, const GString& _code) {return false;}
//===============================================
