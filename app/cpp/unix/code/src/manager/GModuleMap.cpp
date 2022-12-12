//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GModuleNode.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleMap::GModuleMap(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
    m_position = 0;
    m_positionUp = 0;
    m_positionDown = 0;
}
//===============================================
GModuleMap::~GModuleMap() {
    clearMap();
}
//===============================================
GObject* GModuleMap::clone() const {
    return new GModuleMap;
}
//===============================================
GString GModuleMap::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "position", m_position);
    lDom.addData(_code, "node", m_node.toBase64(), true);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleMap::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "module_id").toInt();
    m_position = lDom.getData(_code, "position").toInt();
    m_node = lDom.getData(_code, "node").fromBase64();
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
bool GModuleMap::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
    }
    else if(m_methodName == "save_module_map") {
        onSaveModuleMap();
    }
    else if(m_methodName == "search_module_map") {
        onSearchModuleMap();
    }
    else if(m_methodName == "next_module_map") {
        onNextModuleMap();
    }
    else if(m_methodName == "add_module_map") {
        onAddModuleMap();
    }
    else if(m_methodName == "move_up_module_map") {
        onMoveUpModuleMap();
    }
    else if(m_methodName == "move_down_module_map") {
        onMoveDownModuleMap();
    }
    else {
        GMETHOD_UNKNOWN();
    }
    m_server->addResponse(serialize());
    return true;
}
//===============================================
bool GModuleMap::onSaveModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(!saveModuleMap()) return false;
    if(m_id == 0) {GERROR_ADD(eGERR, "Erreur lors de l'enregistrement de la donnée."); return false;}
    GLOG_ADD(eGLOG, "La donnée a bien été enregistrée.");
    return true;
}
//===============================================
bool GModuleMap::onSearchModuleMap() {
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
    if(!searchModuleMap()) return false;
    if(size() == 0) {GERROR_ADD(eGERR, "Aucun résultat n'a été trouvé."); return false;}
    return true;
}
//===============================================
bool GModuleMap::onNextModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    return true;
}
//===============================================
bool GModuleMap::onAddModuleMap() {
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
bool GModuleMap::onMoveUpModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_position == 0) {GERROR_ADD(eGERR, "Vous devez sélectionner une donnée."); return false;}
    if(!loadPositionUp()) {GERROR_ADD(eGERR, "Impossible de déplacer vers le haut."); return false;}
    if(!updatePositionUp()) {GSAVE_KO(); return false;}
    if(!loadData()) return false;
    return true;
}
//===============================================
bool GModuleMap::onMoveDownModuleMap() {
    if(m_moduleId == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_position == 0) {GERROR_ADD(eGERR, "Vous devez sélectionner une donnée."); return false;}
    if(!loadPositionDown()) {GERROR_ADD(eGERR, "Impossible de déplacer vers le bas."); return false;}
    if(!updatePositionDown()) {GSAVE_KO(); return false;}
    if(!loadData()) return false;
    return true;
}
//===============================================
bool GModuleMap::saveModuleMap() {
    if(m_id == 0) {
        if(m_position == 0) {
            if(!loadPositionAppend()) return false;
        }
        else {
            if(!updatePositionAfter()) return false;
        }
        if(!insertData()) return false;
    }
    else {
        if(!updateData()) return false;
    }
    return true;
}
//===============================================
bool GModuleMap::searchModuleMap() {
    clearMap();
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
        GModuleMap* lObj = new GModuleMap;
        GModuleNode lNode;
        lObj->m_id = lRow.at(j++).toInt();
        lObj->m_position = lRow.at(j++).toInt();
        lObj->m_moduleId = m_moduleId;
        lNode.setModuleId(m_moduleId);
        lNode.setMapId(lObj->m_id);
        lNode.searchModuleNode();
        lObj->m_node = lNode.serialize();
        add(lObj);
    }

    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleMap* lObj = (GModuleMap*)back();
        m_lastId = lObj->m_id;
    }
    return true;
}
//===============================================
bool GModuleMap::countData() {
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
bool GModuleMap::loadData() {
    GMySQL lMySQL;
    GMap lDataMap = lMySQL.readMap(GFORMAT(""
            " select _id, _position "
            " from _module_map "
            " where 1 = 1 "
            " and _module_id = %d "
            " order by _position asc "
            "", m_moduleId
    ));
    clearMap();
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleMap* lObj = new GModuleMap;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_position = lDataRow.at(j++).toInt();
        add(lObj);
    }
    return true;
}
//===============================================
bool GModuleMap::loadPositionAppend() {
    GMySQL lMySQL;
    m_position = lMySQL.readData(GFORMAT(""
            " select max(_position) "
            " from _module_map "
            " where 1 = 1 "
            " and _module_id = %d "
            "", m_moduleId
    )).toInt();
    m_position += 1;
    return true;
}
//===============================================
bool GModuleMap::loadPositionUp() {
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
bool GModuleMap::loadPositionDown() {
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
bool GModuleMap::updatePositionUp() {
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
bool GModuleMap::updatePositionDown() {
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
bool GModuleMap::updatePositionBefore() {
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
bool GModuleMap::updatePositionAfter() {
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
    return true;
}
//===============================================
bool GModuleMap::insertData() {
    if(m_id != 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module_map "
            " ( _module_id, _position ) "
            " values ( %d, %d ) "
            "", m_moduleId
            , m_position
    ))) return false;
    m_id = lMySQL.getId();
    GModuleNode lNode;
    lNode.deserialize(m_node);
    lNode.setMapId(m_id);
    lNode.insertData();
    return true;
}
//===============================================
bool GModuleMap::updateData() {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_map set "
            "   _position = %d "
            " where 1 = 1 "
            " and _id = %d "
            "", m_position
            , m_id
    ))) return false;
    GModuleNode lNode;
    lNode.deserialize(m_node);
    lNode.setMapId(m_id);
    lNode.updateData();
    return true;
}
//===============================================
