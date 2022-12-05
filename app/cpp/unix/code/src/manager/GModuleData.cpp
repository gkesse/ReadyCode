//===============================================
#include "GModuleData.h"
#include "GModule.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleData::GModuleData(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
}
//===============================================
GModuleData::~GModuleData() {
    clearMap(m_map);
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
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleData::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "module_id").toInt();
    m_name = lDom.getData(_code, "name");
    m_value = lDom.getData(_code, "value");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
bool GModuleData::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "save_module_data") {
        onSaveModuleData();
    }
    else if(m_methodName == "search_module_data") {
        onSearchModuleData();
    }
    else if(m_methodName == "search_next_module_data") {
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
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom de la donnée est obligatoire."); return false;}
    if(!saveModuleData()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement du module."); return false;}
    GLOG_ADD(eGLOG, "La donnée a bien été enregistrée.");
    return true;
}
//===============================================
bool GModuleData::onSearchModuleData() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        m_where += GFORMAT(" and _module_id = %d ", m_moduleId);
        if(m_name != "") {
            m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
        }
        if(m_value != "") {
            m_where += GFORMAT(" and _value like '%s%%' ", m_value.c_str());
        }
    }
    if(!countData()) return false;
    if(!searchModuleData()) return false;
    return true;
}
//===============================================
bool GModuleData::onSearchNextModuleData() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    m_where += GFORMAT(" and _module_id = %d ", m_moduleId);
    if(m_name != "") {
        m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
    }
    if(m_value != "") {
        m_where += GFORMAT(" and _value like '%s%%' ", m_value.c_str());
    }
    if(!searchNextModuleData()) return false;
    return true;
}
//===============================================
bool GModuleData::saveModuleData() {
    if(m_id == 0) {
        if(!insertData()) return false;
    }
    else {
        if(!updateData()) {
            onSearchModuleData();
            return false;
        }
    }
    return true;
}
//===============================================
bool GModuleData::searchModuleData() {
    clearMap(m_map);
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name, _value "
            " from _module_data "
            " %s "
            " order by _name asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleData* lObj = new GModuleData;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_value = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleData* lObj = (GModuleData*)m_map.back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleData::searchNextModuleData() {
    clearMap(m_map);
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name, _value "
            " from _module_data "
            " %s "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleData* lObj = new GModuleData;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_value = lDataRow.at(j++);
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleData* lObj = (GModuleData*)m_map.back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleData::countData() {
    GMySQL lMySQL;
    m_dataCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _module_data "
            " %s "
            "", m_where.c_str()
    )).toInt();
    return true;
}
//===============================================
bool GModuleData::existeData() {
    GMySQL lMySQL;
    int lCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _module_data "
            " where 1 = 1 "
            " and _module_id = %d "
            " and _name = '%s' "
            "", m_moduleId
            , m_name.c_str()
    )).toInt();
    if(lCount != 0) {GDATA_EXIST(); return false;}
    return true;
}
//===============================================
bool GModuleData::insertData() {
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
bool GModuleData::updateData() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_data set "
            "   _name = '%s' "
            " , _value = '%s' "
            " where 1 = 1 "
            " and _id = %d "
            "", m_name.c_str()
            , m_value.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================

