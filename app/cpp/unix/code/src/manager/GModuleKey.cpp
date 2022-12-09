//===============================================
#include "GModuleKey.h"
#include "GModule.h"
#include "GModuleType.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
#include "GList.h"
//===============================================
GModuleKey::GModuleKey(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
    m_typeId = 0;
    m_module.reset(new GModule);
    m_moduleType.reset(new GModuleType);
}
//===============================================
GModuleKey::~GModuleKey() {
    clearMap();
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
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "type_id", m_typeId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "label", m_label);
    lDom.addData(_code, m_map);
    lDom.addData(m_module->serialize());
    lDom.addData(m_moduleType->serialize());
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleKey::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_moduleType->deserialize(_data);
    m_module->deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "module_id").toInt();
    m_typeId = lDom.getData(_code, "type_id").toInt();
    m_name = lDom.getData(_code, "name");
    m_label = lDom.getData(_code, "label");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleKey::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleKey::setModuleId(int _moduleId) {
    m_moduleId = _moduleId;
}
//===============================================
bool GModuleKey::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "load_module_key") {
        onLoadModuleKey();
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
bool GModuleKey::onLoadModuleKey() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(!loadModuleKey()) return false;
    return true;
}
//===============================================
bool GModuleKey::onSaveModuleKey() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_name == "") {GERROR_ADD(eGERR, "Le nom de la donnée est obligatoire."); return false;}
    if(m_label == "") {GERROR_ADD(eGERR, "Le libellé de la donnée est obligatoire."); return false;}
    if(m_typeId == 0) {GERROR_ADD(eGERR, "Le type de la donnée est obligatoire."); return false;}
    if(!saveModuleKey()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement de la donnée."); return false;}
    GLOG_ADD(eGLOG, "La donnée a bien été enregistrée.");
    return true;
}
//===============================================
bool GModuleKey::onSearchModuleKey() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        m_where += GFORMAT(" and _module_id = %d ", m_moduleId);
        if(m_name != "") {
            m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
        }
        if(m_label != "") {
            m_where += GFORMAT(" and _label like '%s%%' ", m_label.c_str());
        }
        if(m_typeId != 0) {
            m_where += GFORMAT(" and _module_type_id = %d ", m_typeId);
        }
    }
    if(!countData()) return false;
    if(!searchModuleKey()) return false;
    if(m_map.size() == 0) {GERROR_ADD(eGERR, "Aucun résultat n'a été trouvé."); return false;}
    return true;
}
//===============================================
bool GModuleKey::onSearchNextModuleKey() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(!m_hasData) {GERROR_ADD(eGERR, "Aucune donnée n'a été trouvée."); return false;}
    if(m_lastId != 0) {
        m_where += GFORMAT(" and _id < %d ", m_lastId);
    }
    m_where += GFORMAT(" and _module_id = %d ", m_moduleId);
    if(m_name != "") {
        m_where += GFORMAT(" and _name like '%s%%' ", m_name.c_str());
    }
    if(m_label != "") {
        m_where += GFORMAT(" and _label like '%s%%' ", m_label.c_str());
    }
    if(m_typeId != 0) {
        m_where += GFORMAT(" and _module_type_id = %d ", m_typeId);
    }
    if(!searchNextModuleKey()) return false;
    return true;
}
//===============================================
bool GModuleKey::loadModuleKey() {
    clearMap(m_map);
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _module_id, _module_type_id, _name, _label "
            " from _module_key "
            " where 1 = 1"
            " and _module_id = %d "
            " order by _name asc "
            "", m_moduleId
    ));

    GList lTypeMap;

    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleKey* lObj = new GModuleKey;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_moduleId = lDataRow.at(j++).toInt();
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_label = lDataRow.at(j++);
        m_map.push_back(lObj);
        lTypeMap.push_back(lObj->m_typeId);
    }

    m_moduleType->searchModuleType(lTypeMap);

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
    clearMap(m_map);
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _module_id, _module_type_id, _name, _label "
            " from _module_key "
            " %s "
            " order by _name asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));

    GList lTypeMap;

    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleKey* lObj = new GModuleKey;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_moduleId = lDataRow.at(j++).toInt();
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_label = lDataRow.at(j++);
        m_map.push_back(lObj);
        lTypeMap.push_back(lObj->m_typeId);
    }

    m_module->searchModule(m_moduleId);
    m_moduleType->searchModuleType(lTypeMap);

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
bool GModuleKey::searchKey() {
    clearMap();
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _module_type_id, _name, _label "
            " from _module_key "
            " where 1 = 1 "
            " and _id = %d "
            " and _module_id = %d "
            " order by _name asc "
            "", m_id
            , m_moduleId
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleKey* lObj = new GModuleKey;
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_label = lDataRow.at(j++);
        lObj->m_id = m_id;
        lObj->m_moduleId = m_moduleId;
        add(lObj);
    }
    return true;
}
//===============================================
bool GModuleKey::searchNextModuleKey() {
    clearMap(m_map);
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _module_type_id, _name, _label "
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
        lObj->m_typeId = lDataRow.at(j++).toInt();
        lObj->m_name = lDataRow.at(j++);
        lObj->m_label = lDataRow.at(j++);
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
            " ( _module_id, _module_type_id, _name, _label ) "
            " values ( %d, %d, '%s', '%s' ) "
            "", m_moduleId
            , m_name.c_str()
            , m_label.c_str()
            , m_typeId
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
            " , _label = '%s' "
            " , _module_type_id = %d "
            " where 1 = 1 "
            " and _id = %d "
            "", m_name.c_str()
            , m_label.c_str()
            , m_typeId
            , m_id
    ))) return false;
    return true;
}
//===============================================

