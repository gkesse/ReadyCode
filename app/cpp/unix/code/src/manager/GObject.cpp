//===============================================
#include "GCode.h"
#include "GObject.h"
#include "GPath.h"
//===============================================
GObject::GObject() {
    clearMap();
}
//===============================================
GObject::~GObject() {

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
    if(_index >= 0 && _index < m_map.size()) {
        return m_map.at(_index);
    }
    return 0;
}
//===============================================
GObject* GObject::back() {
    return m_map.back();
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
void GObject::showErrors() {
    m_logs.showErrors();
}
//===============================================
void GObject::addLogs(const GLog& _obj) {
    m_logs.addLogs(_obj);
}
//===============================================
const GLog& GObject::getLogs() const {
    return m_logs;
}
//===============================================
GString GObject::getResponse() const {
    return m_responseXml.toString();
}
//===============================================
GString GObject::toJson() {
    GCode lDom;
    lDom.loadXml(serialize());
    return lDom.toJson();
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code)  {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
