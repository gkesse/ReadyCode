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
GManager::GManager() : GSearch() {
    m_id = 0;
    m_code = "";
    m_label = "";
}
//===============================================
GManager::~GManager() {

}
//===============================================
GObject* GManager::clone() {
    return new GManager;
}
//===============================================
std::string GManager::serialize(bool _isParent, const std::string& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "code_id", m_code);
    lDom.addData(_code, "label", m_label);
    lDom.addData(_code, m_map);
    if(_isParent) {
        lDom.loadCode(GSearch::serialize());
    }
    return lDom.toStringData();
}
//===============================================
void GManager::deserialize(const std::string& _data, const std::string& _code) {
    GSearch::deserialize(_data);
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
    else if(m_method == "next_code") {
        onNextCode(_client);
    }
    //===============================================
    else if(m_method == "update_code") {
        onUpdateCode(_client);
    }
    //===============================================
    else if(m_method == "delete_code") {
        onDeleteCode(_client);
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
bool GManager::onNextCode(GSocket* _client) {
    searchCode();
    std::string lData = serialize();
    _client->addResponse(lData);
    return true;
}
//===============================================
bool GManager::onUpdateCode(GSocket* _client) {
    updateCode();
    std::string lData = serialize();
    _client->addResponse(lData);
    return true;
}
//===============================================
bool GManager::onDeleteCode(GSocket* _client) {
    deleteCode();
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
    loadId();
    if(m_id != 0) {GERROR(eGERR, "Le code existe déjà."); return false;}
    saveData();
    return true;
}
//===============================================
bool GManager::searchCode() {
    if(m_id != 0) {
        m_where += sformat(" and _id = %d ", m_id);
    }
    else {
        if(m_code != "") {
            m_where += sformat(" and _code like lower('%%%s%%') ", m_code.c_str());
        }
    }
    //
    if(m_dataSize == 0) {GERROR(eGERR, "La taille des codes n'est pas définie."); return false;}
    loadDataCount();
    if(m_dataCount == 0) {GERROR(eGERR, "La table ne contient pas de codes."); return false;}
    if(m_lastId < 0) {
        loadLastId();
        if(m_lastId <= 0) {GERROR(eGERR, "La table ne contient pas d'index."); return false;}
    }
    //
    loadDataMap();
    return true;
}
//===============================================
bool GManager::updateCode() {
    if(m_id != 0) {
        m_where += sformat(" and _id = %d ", m_id);
    }
    else {
        if(m_code != "") {
            m_where += sformat(" and _code like lower('%%%s%%') ", m_code.c_str());
        }
    }
    //
    if(m_dataSize == 0) {GERROR(eGERR, "La taille des codes n'est pas définie."); return false;}
    loadDataCount();
    if(m_dataCount == 0) {GERROR(eGERR, "La table ne contient pas de codes."); return false;}
    if(m_lastId < 0) {
        loadLastId();
        if(m_lastId <= 0) {GERROR(eGERR, "La table ne contient pas d'index."); return false;}
    }
    //
    loadDataMap();
    return true;
}
//===============================================
bool GManager::updateCode() {
    if(m_id == 0) {GERROR(eGERR, "L'identifiant n'est pas défini."); return false;}
    GMySQL().execQuery(sformat(""
            " update _code "
            " set _code = '%s' "
            " , _label = '%s' "
            " where _id = %d "
            "", m_code.c_str()
            , m_label.c_str()
            , m_id));
    return true;
}
//===============================================
bool GManager::deleteCode() {
    if(m_id == 0) {GERROR(eGERR, "L'identifiant n'est pas défini."); return false;}
    GMySQL().execQuery(sformat(""
            " delete from _code "
            " where _id = %d "
            "", m_id));
    return true;
}
//===============================================
bool GManager::loadId() {
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
bool GManager::loadLastId() {
    std::string lLastId = GMySQL().readData(sformat(""
            " select _id "
            " from _code "
            " order by _id desc "
            " limit 1 "
            ""
    ));

    m_lastId = GString(lLastId).toInt() + 1;
    return true;
}
//===============================================
bool GManager::loadDataCount() {
    std::string lCount = GMySQL().readData(sformat(""
            " select count(*) "
            " from _code "
            " %s "
            " order by _id desc "
            "", m_where.c_str()
    ));

    m_dataCount = GString(lCount).toInt();
    return true;
}
//===============================================
bool GManager::loadDataMap() {
    std::vector<std::vector<std::string>> lMap = GMySQL().readMap(sformat(""
            " select _id, _code, _label "
            " from _code "
            " %s "
            " and _id < %d "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_lastId
            , m_dataSize
    ));

    int lSize = (int)lMap.size();
    for(int i = 0; i < lSize; i++) {
        std::vector<std::string> lRow = lMap.at(i);
        GManager* lManager = new GManager;
        int j = 0;
        lManager->m_id = GString(lRow.at(j++)).toInt();
        lManager->m_code = lRow.at(j++);
        lManager->m_label = lRow.at(j++);
        m_map.push_back(lManager);
        //
        if(i == lSize - 1) {
            m_lastId = lManager->m_id;
        }
    }
    m_dataOffset += m_dataSize;
    return true;
}
//===============================================
bool GManager::saveData() {
    if(m_id == 0) return insertData();
    return updateData();
}
//===============================================
bool GManager::insertData() {
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
bool GManager::updateData() {
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
