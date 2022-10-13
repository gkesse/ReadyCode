//===============================================
#include "GModuleData.h"
#include "GModule.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleData::GModuleData()
: GSearch() {
    m_codeName = "module_data";
    initModuleData();
}
//===============================================
GModuleData::~GModuleData() {
    delete m_module;
}
//===============================================
GObject* GModuleData::clone() const {
    return new GModuleData;
}
//===============================================
GString GModuleData::serialize() const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(m_codeName, "id", m_id);
    lDom.addData(m_codeName, "name", m_name);
    lDom.addData(m_codeName, "value", m_value);
    lDom.addData(m_codeName, m_map);
    lDom.loadData(m_module->serialize());
    lDom.loadData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleData::deserialize(const GString& _data) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(m_codeName, "id").toInt();
    m_name = lDom.getData(m_codeName, "name");
    m_value = lDom.getData(m_codeName, "value");
    lDom.getData(m_codeName, m_map, this);
    return true;
}
//===============================================
void GModuleData::initModuleData() {
    m_id = 0;
    m_module = new GModule;
    m_where = " where 1 = 1 ";
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
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom de la donnée est obligatoire."); return false;}
    if(!saveModuleData()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement du module."); return false;}
    GSAVE_OK();
    return true;
}
//===============================================
bool GModuleData::onSearchModuleData() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        m_where += GFORMAT(" and _module_id = %d ", m_module->getId());
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
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    m_where += GFORMAT(" and _module_id = %d ", m_module->getId());
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
        if(!existeData()) return false;
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
bool GModuleData::searchNextModuleData() {
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
            "", m_module->getId()
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
            "", m_module->getId()
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
            " where _id = %d "
            "", m_name.c_str()
            , m_value.c_str()
            , m_id
    ))) return false;
    return true;
}
//===============================================

