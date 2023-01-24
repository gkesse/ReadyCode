//===============================================
#include "GPage.h"
//===============================================
GPage::GPage()
: GSearch() {
    m_id = 0;
}
//===============================================
GPage::~GPage() {

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
    GSearch::deserialize(_data);
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
bool GPage::run(const GString& _request) {
    deserialize(_request);
    if(m_methodName == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(m_methodName == "page") {
        onSavePage();
    }
    else {
        m_logs.addError("La méthode est inconnu.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPage::onSavePage() {
    for(int i = 0; i < 3; i++) {
        GPage* lObj = new GPage;
        lObj->m_id = i + 1;
        lObj->m_name = "admin";
        lObj->m_title = "Administration";
        lObj->m_url = "home/admin";
        lObj->m_path = "/path/home/admin.php";
        m_map.push_back(lObj);
    }
    m_logs.addLog("La donnée a bien été enregistrée.");
    return !m_logs.hasErrors();
}
//===============================================
