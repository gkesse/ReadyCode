//===============================================
#include "GModuleKey.h"
#include "GModule.h"
#include "GModuleType.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleKey::GModuleKey(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_type = 0;
    m_module.reset(new GModule);
    m_moduleType.reset(new GModuleType);
}
//===============================================
GModuleKey::~GModuleKey() {
    clearMap(m_map);
}
//===============================================
GObject* GModuleKey::clone() const {
    return new GModuleKey;
}
//===============================================
GString GModuleKey::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, m_map);
    lDom.addData(m_module->serialize());
    lDom.addData(m_moduleType->serialize());
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleKey::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
    m_moduleType->deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_name = lDom.getData(_code, "name");
    m_type = lDom.getData(_code, "type").toInt();
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
bool GModuleKey::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "save_module_key") {
        onSaveModuleKey();
    }
    else if(m_methodName == "search_module_key") {
        onSearchModuleKey();
    }
    else if(m_methodName == "search_next_module_key") {
        onSearchNextModuleKey();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModuleKey::onSaveModuleKey() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom de la donnée est obligatoire."); return false;}
    if(m_moduleType->getId() == 0) {GERROR_ADD(eGERR, "Le type de la donnée est obligatoire."); return false;}
    if(!saveModuleKey()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement de la donnée."); return false;}
    GLOG_ADD(eGLOG, "La donnée a bien été enregistrée.");
    return true;
}
//===============================================
bool GModuleKey::onSearchModuleKey() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        m_where += GFORMAT(" and _module_id = %d ", m_module->getId());
        if(m_name != "") {
            m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
        }
        if(m_moduleType->getId() != 0) {
            m_where += GFORMAT(" and _module_type_id = %d ", m_moduleType->getId());
        }
    }
    if(!countData()) return false;
    if(!searchModuleKey()) return false;
    return true;
}
//===============================================
bool GModuleKey::onSearchNextModuleKey() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    m_where += GFORMAT(" and _module_id = %d ", m_module->getId());
    if(m_name != "") {
        m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
    }
    if(m_moduleType->getId() != 0) {
        m_where += GFORMAT(" and _module_type_id = %d ", m_moduleType->getId());
    }
    if(!searchNextModuleKey()) return false;
    return true;
}
//===============================================
bool GModuleKey::saveModuleKey() {
    if(m_id == 0) {
        if(!insertData()) return false;
    }
    else {
        if(!updateData()) {
            onSearchModuleKey();
            return false;
        }
    }
    return true;
}
//===============================================
bool GModuleKey::searchModuleKey() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name, _module_type_id "
            " from _module_key "
            " %s "
            " order by _name asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleKey* lObj = new GModuleKey;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_type = lDataRow.at(j++).toInt();
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleKey* lObj = (GModuleKey*)m_map.back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleKey::searchNextModuleKey() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _name, _module_type_id "
            " from _module_key "
            " %s "
            " order by _id desc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleKey* lObj = new GModuleKey;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_type = lDataRow.at(j++).toInt();
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleKey* lObj = (GModuleKey*)m_map.back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleKey::countData() {
    GMySQL lMySQL;
    m_dataCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _module_key "
            " %s "
            "", m_where.c_str()
    )).toInt();
    return true;
}
//===============================================
bool GModuleKey::insertData() {
    if(m_id != 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module_key "
            " ( _module_id, _name, _module_type_id ) "
            " values ( %d, '%s', %d ) "
            "", m_module->getId()
            , m_name.c_str()
            , m_moduleType->getId()
    ))) return false;
    m_id = lMySQL.getId();
    return true;
}
//===============================================
bool GModuleKey::updateData() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_key set "
            "   _name = '%s' "
            " , _module_type_id = %d "
            " where _id = %d "
            "", m_name.c_str()
            , m_moduleType->getId()
            , m_id
    ))) return false;
    return true;
}
//===============================================

