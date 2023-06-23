//===============================================
#include "GFacade.h"
//===============================================
GFacade::GFacade()
: GObject() {

}
//===============================================
GFacade::~GFacade() {

}
//===============================================
void GFacade::setFacade(const GString& _facade) {
    m_facade = _facade;
}
//===============================================
GString GFacade::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "facade", m_facade);
    return lDom.toString();
}
//===============================================
void GFacade::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_facade = lDom.getData(_code, "facade");
}
//===============================================
