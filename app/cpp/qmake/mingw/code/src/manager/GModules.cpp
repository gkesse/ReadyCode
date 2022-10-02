//===============================================
#include "GModules.h"
#include "GCode.h"
#include "GClient.h"
//===============================================
GModules::GModules()
: GModule() {
    m_id = 0;
}
//===============================================
GModules::~GModules() {

}
//===============================================
GObject* GModules::clone() const {
    return new GModules;
}
//===============================================
GString GModules::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    return lDom.toString();
}
//===============================================
bool GModules::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    return true;
}
//===============================================
void GModules::assign(const GModules& _modules) {
    m_id = _modules.m_id;
    m_name = _modules.m_name;
}
//===============================================
void GModules::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
GString GModules::getName() const {
    return m_name;
}
//===============================================
void GModules::createModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "create_module", lData);
    deserialize(lData);
}
//===============================================
void GModules::searchModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "search_module", lData);
    deserialize(lData);
}
//===============================================
void GModules::deleteModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "delete_module", lData);
    deserialize(lData);
}
//===============================================
