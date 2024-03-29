//===============================================
#include "GObject.h"
#include "GPath.h"
#include "GCode.h"
//===============================================
GObject::GObject() {

}
//===============================================
GObject::~GObject() {

}
//===============================================
void GObject::clearMap() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GObject* lObj = m_map.at(i);
        delete lObj;
    }
    m_map.clear();
}
//===============================================
int GObject::size() const {
    return (int)m_map.size();
}
//===============================================
GObject* GObject::at(int _index) const {
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
    printf("%s\n", serialize().c_str());
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code) {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
