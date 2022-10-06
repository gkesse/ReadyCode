//===============================================
#include "GModuleData.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleData::GModuleData()
: GSearch() {
    initModules();
}
//===============================================
GModuleData::~GModuleData() {

}
//===============================================
GObject* GModuleData::clone() const {
    return new GModuleData;
}
//===============================================
GString GModuleData::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "modules_id", m_moduleId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map);
    lDom.loadData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleData::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "modules_id").toInt();
    m_name = lDom.getData(_code, "name");
    m_value = lDom.getData(_code, "value");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleData::initModules() {
    m_id = 0;
    m_moduleId = 0;
    m_where = " where 1 = 1 ";
}
//===============================================
bool GModuleData::onModule() {
    deserialize(m_server->getRequest());
    if(m_method == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_method == "save_module_data") {
        onSaveModuleData();
    }
    else if(m_method == "search_module_data") {
        onSearchModuleData();
    }
    else if(m_method == "search_next_module_data") {
        onSearchNextModuleData();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModuleData::onSaveModuleData() {
    if(m_moduleId != 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom de la donnée est obligatoire."); return false;}
    if(!saveModulesData()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement du module."); return false;}
    GLOG_ADD(eGLOG, "Le module a bien été enregistré.");
    return true;
}
//===============================================
bool GModuleData::onSearchModuleData() {
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        if(m_name != "") {
            m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
        }
    }
    if(!countModuleData()) return false;
    if(!searchModulesData()) return false;
    return true;
}
//===============================================
bool GModuleData::onSearchNextModuleData() {
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    if(m_name != "") {
        m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
    }
    if(!searchNextModuleData()) return false;
    return true;
}
//===============================================
bool GModuleData::saveModulesData() {
    if(m_id == 0) {
        if(!insertModuleData()) return false;
    }
    else {
        if(!updateModuleData()) {
            onSearchModuleData();
            return false;
        }
    }
    return true;
}
//===============================================
bool GModuleData::searchModulesData() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module "
            " %s "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleData* lModule = new GModuleData;
        lModule->m_id = lDataRow.at(j++).toInt();
        lModule->m_name = lDataRow.at(j++);
        m_map.push_back(lModule);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleData* lModule = (GModuleData*)m_map.back();
        m_lastId = lModule->m_id;
    }
    return true;
}
//===============================================
bool GModuleData::searchNextModuleData() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name "
            " from _module "
            " %s "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleData* lModule = new GModuleData;
        lModule->m_id = lDataRow.at(j++).toInt();
        lModule->m_name = lDataRow.at(j++);
        m_map.push_back(lModule);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleData* lModule = (GModuleData*)m_map.back();
        m_lastId = lModule->m_id;
    }
    return true;
}
//===============================================
bool GModuleData::countModuleData() {
    GMySQL lMySQL;
    m_dataCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _module "
            " %s "
            "", m_where.c_str()
    )).toInt();
    return true;
}
//===============================================
bool GModuleData::insertModuleData() {
    if(m_id != 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module_data "
            " ( _module_id, _name, _value ) "
            " values ( %d, '%s', '%s' ) "
            "", m_moduleId
            , m_name.c_str()
            , m_value.c_str()
    ))) return false;
    m_id = lMySQL.getId();
    return true;
}
//===============================================
bool GModuleData::updateModuleData() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module set "
            "   _module_id = %d "
            " , _name = '%s' "
            " , _value = '%s' "
            " where _id = %d "
            "", m_moduleId
            , m_name.c_str()
            , m_value.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================

