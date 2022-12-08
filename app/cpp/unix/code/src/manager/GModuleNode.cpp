//===============================================
#include "GModuleNode.h"
#include "GModule.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleNode::GModuleNode(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
    m_keyId = 0;
    m_position = 0;
    m_positionUp = 0;
    m_positionDown = 0;
}
//===============================================
GModuleNode::~GModuleNode() {
    clearMap();
}
//===============================================
GObject* GModuleNode::clone() const {
    return new GModuleNode;
}
//===============================================
GString GModuleNode::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "key_id", m_keyId);
    lDom.addData(_code, "position", m_position);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleNode::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "module_id").toInt();
    m_keyId = lDom.getData(_code, "key_id").toInt();
    m_position = lDom.getData(_code, "position").toInt();
    m_value = lDom.getData(_code, "value");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
bool GModuleNode::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "save_module_node") {
        onSaveModuleMap();
    }
    else if(m_methodName == "search_module_node") {
        onSearchModuleMap();
    }
    else if(m_methodName == "next_module_node") {
        onNextModuleMap();
    }
    else if(m_methodName == "add_module_node") {
        onAddModuleMap();
    }
    else if(m_methodName == "move_up_module_node") {
        onMoveUpModuleMap();
    }
    else if(m_methodName == "move_down_module_node") {
        onMoveDownModuleMap();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModuleNode::onSaveModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(!checkData()) return false;
    if(m_position == 0) {
        if(!loadPositionAppend()) return false;
    }
    else {
        if(!updatePositionAfter()) return false;
    }
    if(!saveModuleMap()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement de la donnée."); return false;}
    GLOG_ADD(eGLOG, "La donnée a bien été enregistrée.");
    return true;
}
//===============================================
bool GModuleNode::onSearchModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        m_where += GFORMAT(" and _module_id = %d ", m_moduleId);
        if(m_position != 0) {
            m_where += GFORMAT(" and _position = %d ", m_position);
        }
    }
    if(!countData()) return false;
    if(!searchData()) return false;
    if(m_map.size() == 0) {GERROR_ADD(eGERR, "Aucun résultat n'a été trouvé."); return false;}
    return true;
}
//===============================================
bool GModuleNode::onNextModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    return true;
}
//===============================================
bool GModuleNode::onAddModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_position == 0) {
        if(!loadPositionAppend()) return false;
    }
    else {
        if(!updatePositionAfter()) return false;
    }
    if(!insertData()) return false;
    if(!loadData()) return false;
    return true;
}
//===============================================
bool GModuleNode::onMoveUpModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_position == 0) {GERROR_ADD(eGERR, "Vous devez sélectionner une donnée."); return false;}
    if(!loadPositionUp()) {GERROR_ADD(eGERR, "Impossible de déplacer vers le haut."); return false;}
    if(!updatePositionUp()) {GSAVE_KO(); return false;}
    if(!loadData()) return false;
    return true;
}
//===============================================
bool GModuleNode::onMoveDownModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_position == 0) {GERROR_ADD(eGERR, "Vous devez sélectionner une donnée."); return false;}
    if(!loadPositionDown()) {GERROR_ADD(eGERR, "Impossible de déplacer vers le bas."); return false;}
    if(!updatePositionDown()) {GSAVE_KO(); return false;}
    if(!loadData()) return false;
    return true;
}
//===============================================
bool GModuleNode::checkData() {
    for(int i = 0; i < size(); i++) {
        GModuleNode* lObj = (GModuleNode*)at(i);
        if(lObj->m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module d'une donnée est obligatoire."); return false;}
        if(lObj->m_keyId == 0) {GERROR_ADD(eGERR, "L'identifiant de la clé d'une donnée est obligatoire."); return false;}
        if(lObj->m_value == "") {GERROR_ADD(eGERR, "La valeur d'une donnée est obligatoire."); return false;}
    }
    return true;
}
//===============================================
bool GModuleNode::saveModuleMap() {
    if(m_id == 0) {
        if(!insertData()) return false;
    }
    else {
        if(!updateData()) {
            //onSearchModuleMap();
            return false;
        }
    }
    return true;
}
//===============================================
bool GModuleNode::countData() {
    GMySQL lMySQL;
    m_dataCount = lMySQL.readData(GFORMAT(""
            " select count(*) "
            " from _module_map "
            " %s "
            "", m_where.c_str()
    )).toInt();
    return true;
}
//===============================================
bool GModuleNode::searchData() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _position "
            " from _module_map "
            " %s "
            " order by _position asc "
            " limit %d "
            "", m_where.c_str()
            , m_dataSize
    ));
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lRow = lDataMap.at(i);
        int j = 0;
        GModuleNode* lObj = new GModuleNode;
        lObj->m_id = lRow.at(j++).toInt();
        lObj->m_position = lRow.at(j++).toInt();
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleNode* lObj = (GModuleNode*)m_map.back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleNode::loadData() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _position "
            " from _module_map "
            " where 1 = 1 "
            " and _module_id = %d "
            " order by _position asc "
            "", m_moduleId
    ));
    clearMap(m_map);
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleNode* lObj = new GModuleNode;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_position = lDataRow.at(j++).toInt();
        m_map.push_back(lObj);
    }
    return true;
}
//===============================================
bool GModuleNode::loadPositionAppend() {
    GMySQL lMySQL;
    m_position = lMySQL.readData(GFORMAT(""
            " select max(_position) "
            " from _module_map "
            " where 1 = 1 "
            " and _module_id = %d "
            "", m_moduleId
    )).toInt();
    m_position += 1;
    for(int i = 0; i < size(); i++) {
        GModuleNode* lObj = (GModuleNode*)at(i);
        lObj->m_position = m_position;
    }
    return true;
}
//===============================================
bool GModuleNode::loadPositionUp() {
    GMySQL lMySQL;
    m_positionUp = lMySQL.readData(GFORMAT(""
            " select max(_position) "
            " from _module_map "
            " where 1 = 1 "
            " and _position < %d "
            " and _module_id = %d "
            "", m_position
            , m_moduleId
    )).toInt();
    if(m_positionUp == 0) return false;
    return true;
}
//===============================================
bool GModuleNode::loadPositionDown() {
    GMySQL lMySQL;
    m_positionDown = lMySQL.readData(GFORMAT(""
            " select min(_position) "
            " from _module_map "
            " where 1 = 1 "
            " and _position > %d "
            " and _module_id = %d "
            "", m_position
            , m_moduleId
    )).toInt();
    if(m_positionDown == 0) return false;
    return true;
}
//===============================================
bool GModuleNode::updatePositionUp() {
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_map set "
            " _position = %d + %d - _position "
            " where 1 = 1 "
            " and _module_id = %d "
            " and _position in ( %d, %d )"
            "", m_position
            , m_positionUp
            , m_moduleId
            , m_position
            , m_positionUp
    ))) return false;
    m_position = m_positionUp;
    return true;
}
//===============================================
bool GModuleNode::updatePositionDown() {
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_map set "
            " _position = %d + %d - _position "
            " where 1 = 1 "
            " and _module_id = %d "
            " and _position in ( %d, %d )"
            "", m_position
            , m_positionDown
            , m_moduleId
            , m_position
            , m_positionDown
    ))) return false;
    m_position = m_positionDown;
    return true;
}
//===============================================
bool GModuleNode::updatePositionBefore() {
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_map set "
            " _position = _position + 1 "
            " where 1 = 1 "
            " and _module_id = %d "
            " and _position >= %d "
            "", m_moduleId
            , m_position
    ))) return false;
    return true;
}
//===============================================
bool GModuleNode::updatePositionAfter() {
    GMySQL lMySQL;
    m_position += 1;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_map set "
            " _position = _position + 1 "
            " where 1 = 1 "
            " and _module_id = %d "
            " and _position >= %d "
            "", m_moduleId
            , m_position
    ))) return false;
    for(int i = 0; i < size(); i++) {
        GModuleNode* lObj = (GModuleNode*)at(i);
        lObj->m_position = m_position;
    }
    return true;
}
//===============================================
bool GModuleNode::insertData() {
    for(int i = 0; i < size(); i++) {
        GModuleNode* lObj = (GModuleNode*)at(i);
        insertData(lObj);
    }
    return true;
}
//===============================================
bool GModuleNode::insertData(GModuleNode* _obj) {
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module_map "
            " ( _module_id, _position, _key_id, _value ) "
            " values ( %d, %d, %d, '%s' ) "
            "", _obj->m_moduleId
            , _obj->m_position
            , _obj->m_keyId
            , _obj->m_value.c_str()
    ))) return false;
    _obj->m_id = lMySQL.getId();
    return true;
}
//===============================================
