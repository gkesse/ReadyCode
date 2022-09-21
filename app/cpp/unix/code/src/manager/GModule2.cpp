//===============================================
#include "GModule2.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket2.h"
#include "GCode2.h"
//===============================================
GModule2::GModule2()
: GObject() {
    m_client = 0;
}
//===============================================
GModule2::~GModule2() {
    for(int i = 0; i < m_map.size(); i++) {
        GModule2* lObj = m_map.at(i);
        delete lObj;
    }
}
//===============================================
GString2 GModule2::serialize(const GString2& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
bool GModule2::deserialize(const GString2& _data, const GString2& _code) {
    GCode2 lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
    return true;
}
//===============================================
void GModule2::setClient(GSocket2* _client) {
    m_client = _client;
}
//===============================================
void GModule2::setModule(const GString2& _module) {
    m_module = _module;
}
//===============================================
void GModule2::setMethod(const GString2& _method) {
    m_method = _method;
}
//===============================================
void GModule2::print() const {
    printf("%s\n", serialize().c_str());
}
//===============================================
