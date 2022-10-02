//===============================================
#include "GModules.h"
#include "GCode2.h"
#include "GClient.h"
//===============================================
GModules::GModules()
: GModule2() {
    m_id = 0;
}
//===============================================
GModules::~GModules() {

}
//===============================================
GObject2* GModules::clone() const {
    return new GModules;
}
//===============================================
GString GModules::serialize(const GString& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    return lDom.toString();
}
//===============================================
bool GModules::deserialize(const GString& _data, const GString& _code) {
    GCode2 lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    return true;
}
//===============================================
void GModules::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
void GModules::createModule() {
    GString lData = serialize();
    lData = GCALL_SERVER("module", "create_module", lData);
    deserialize(lData);
}
//===============================================
