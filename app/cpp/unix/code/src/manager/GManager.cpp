//===============================================
#include "GManager.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GMySQL.h"
#include "GSocket.h"
#include "GString.h"
#include "GMd5.h"
#include "GDefine.h"
//===============================================
GManager::GManager() : GModule() {
    m_id = 0;
    m_code = "";
    m_label = "";
    m_where = " where 1 ";
    m_orderBy = " order by desc _id ";
}
//===============================================
GManager::~GManager() {

}
//===============================================
GObject* GManager::clone() {
    return new GManager;
}
//===============================================
std::string GManager::serialize(const std::string& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "code_id", m_code);
    lDom.addData(_code, "label", m_label);
    lDom.addData(_code, m_map);
    return lDom.toStringCode(_code);
}
//===============================================
void GManager::deserialize(const std::string& _data, const std::string& _code) {
    GModule::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = GString(lDom.getItem(_code, "id")).toInt();
    m_code = lDom.getItem(_code, "code_id");
    m_label = lDom.getItem(_code, "label");
    lDom.getItem(_code, m_map, this);
}
//===============================================
bool GManager::onModule(GSocket* _client) {
    deserialize(_client->toReq());
    //===============================================
    if(m_method == "") {
        onMethodNone(_client);
        return false;
    }
    //===============================================
    // method
    //===============================================
    else if(m_method == "create_code") {
        onCreateCode(_client);
    }
    //===============================================
    else if(m_method == "search_code") {
        onSearchCode(_client);
    }
    //===============================================
    // unknown
    //===============================================
    else {
        onMethodUnknown(_client);
        return false;
    }
    //===============================================
    return true;
}
//===============================================
bool GManager::onCreateCode(GSocket* _client) {
    createCode();
    std::string lData = serialize();
    _client->addResponse(lData);
    return true;
}
//===============================================
bool GManager::onSearchCode(GSocket* _client) {
    searchCode();
    std::string lData = serialize();
    _client->addResponse(lData);
    return true;
}
//===============================================
bool GManager::createCode() {
    if(m_code == "") {GERROR(eGERR, "Le code est obligatoire."); return false;}
    if(m_code.size() < 3) {GERROR(eGERR, "Le code doit faire au minimum 8 caractères."); return false;}
    if(m_code.size() > 50) {GERROR(eGERR, "Le code doit faire au maximum 50 caractères."); return false;}
    if(m_label.size() > 50) {GERROR(eGERR, "Le libellé doit faire au maximum 50 caractères."); return false;}
    loadCodeId();
    if(m_id != 0) {GERROR(eGERR, "Le code existe déjà."); return false;}
    saveCode();
    return true;
}
//===============================================
bool GManager::searchCode() {
    if(m_id != 0) {m_where += sformat(" and _id = %d ", m_id);}
    else {
        if(m_code != "") {m_where += sformat(" and _code like lower('%%%s%%') ", m_code.c_str());}
    }
    loadCodeMap();
    return true;
}
//===============================================
bool GManager::loadCodeId() {
    if(m_code == "") return false;
    std::string lData = GMySQL().readData(sformat(""
            " select _id "
            " from _code "
            " where _code = lower('%s') "
            "", m_code.c_str()
    ));
    m_id = GString(lData).toInt();
    return true;
}
//===============================================
bool GManager::loadCode() {
    if(m_id == 0) return false;

    std::vector<std::string> lRow = GMySQL().readRow(sformat(""
            " select _id, _code, _label "
            " from _code "
            " where _id = %d "
            "", m_id
    ));

    int i = 0;
    m_id = GString(lRow.at(i++)).toInt();
    m_code = lRow.at(i++);
    m_label = lRow.at(i++);
    return true;
}
//===============================================
bool GManager::loadCodeMap() {
    std::vector<std::vector<std::string>> lMap = GMySQL().readMap(sformat(""
            " select _id, _code, _label "
            " from _code "
            " %s %s "
            "", m_where.c_str()
            , m_orderBy.c_str()
    ));

    for(int i = 0; i < (int)lMap.size(); i++) {
        std::vector<std::string> lRow = lMap.at(i);
        GManager* lManager = new GManager;
        int j = 0;
        lManager->m_id = GString(lRow.at(j++)).toInt();
        lManager->m_code = lRow.at(j++);
        lManager->m_label = lRow.at(j++);
        m_map.push_back(lManager);
    }

    return true;
}
//===============================================
bool GManager::saveCode() {
    if(m_id == 0) return insertCode();
    return updateCode();
}
//===============================================
bool GManager::insertCode() {
    if(m_id != 0) return false;
    if(m_code == "") return false;

    m_id = GMySQL().execQuery(sformat(""
            " insert into _code "
            " ( _code, _label ) "
            " values ( lower('%s'), '%s' ) "
            "", m_code.c_str()
            , m_label.c_str()
    )).getId();

    return true;
}
//===============================================
bool GManager::updateCode() {
    if( m_id == 0) return false;
    if(m_code == "") return false;

    GMySQL().execQuery(sformat(""
            " update _user "
            " set _code = '%s' "
            " , _label = '%s' "
            " where _id = %d "
            "", m_code.c_str()
            , m_label.c_str()
            , m_id
    ));

    return true;
}
//===============================================
