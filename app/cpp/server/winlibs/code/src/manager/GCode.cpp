//===============================================
#include "GCode.h"
//===============================================
GCode::GCode()
: GXml() {

}
//===============================================
GCode::~GCode() {

}
//===============================================
xmlNodePtr GCode::createDatas() {
    GCode lDom;
    lDom.m_node = getNode(*this, sformat("/rdv/datas"));
    if(!lDom.m_node) {
        lDom.createNode(*this, sformat("/rdv/datas"));
    }
    return lDom.m_node;
}
//===============================================
xmlNodePtr GCode::createCode(const GString& _code) {
    GCode lDom;
    lDom.m_node = getNode(*this, sformat("/rdv/datas/data[code='%s']", _code.c_str()));
    if(!lDom.m_node) {
        lDom.m_node = createDatas();
        lDom.m_node = lDom.addObj("data");
        lDom.GXml::addData("code", _code);
    }
    return lDom.m_node;
}
//===============================================
void GCode::addData(const GString& _code, const GString& _name, const GString& _value) {
    if(_value.isEmpty()) return;
    GCode lDom;
    lDom.m_node = getNode(*this, sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _name.c_str()));
    if(!lDom.m_node) {
        lDom.m_node = createCode(_code);
        lDom.GXml::addData(_name, _value);
    }
    else {
        lDom.setValue(_value);
    }
}
//===============================================
