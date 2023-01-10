//===============================================
#include "GPage.h"
//===============================================
GPage::GPage()
: GSearch() {
    m_id = 0;
}
//===============================================
GPage::~GPage() {
    clearMap();
}
//===============================================
GString GPage::serialize(const GString& _code)  {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "title", m_title);
    lDom.addData(_code, "url", m_url);
    lDom.addData(_code, "path", m_name);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
void GPage::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    m_title = lDom.getData(_code, "title");
    m_url = lDom.getData(_code, "url");
    m_path = lDom.getData(_code, "path");
    lDom.getData(_code, m_map, this);
}
//===============================================
GObject* GPage::clone() const {
    GPage* lObj = new GPage;
    lObj->setPage(*this);
    return lObj;
}
//===============================================
void GPage::setPage(const GPage& _obj) {
    m_id = _obj.m_id;
    m_name = _obj.m_name;
    m_title = _obj.m_title;
    m_url = _obj.m_url;
    m_path = _obj.m_path;
}
//===============================================
