//===============================================
#include "GManager.h"
//===============================================
GManager::GManager()
: GFacade() {

}
//===============================================
GManager::~GManager() {

}
//===============================================
GString GManager::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
void GManager::deserialize(const GString& _data, const GString& _code) {
    GFacade::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
}
//===============================================
