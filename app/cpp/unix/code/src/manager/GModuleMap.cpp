//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GModuleMap::GModuleMap(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_position = 0;
    m_positionUp = 0;
    m_positionDown = 0;
    m_module.reset(new GModule);
}
//===============================================
GModuleMap::~GModuleMap() {
    clearMap(m_map);
}
//===============================================
GObject* GModuleMap::clone() const {
    return new GModuleMap;
}
//===============================================
GString GModuleMap::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "position", m_position);
    lDom.addData(_code, m_map);
    lDom.addData(m_module->serialize());
    lDom.addData(GSearch::serialize());
    return lDom.toString();
}
//===============================================
bool GModuleMap::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_position = lDom.getData(_code, "position").toInt();
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
bool GModuleMap::onModule() {
    deserialize(m_server->getRequest());
    if(m_methodName == "") {
        GMETHOD_REQUIRED();
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
bool GModuleMap::onSearchModuleMap() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_id != 0) {
        m_where += GFORMAT(" and _id = %d ", m_id);
    }
    else {
        m_where += GFORMAT(" and _module_id = %d ", m_module->getId());
        if(m_position != 0) {
            m_where += GFORMAT(" and _position = %d ", m_position);
        }
    }
    if(!countData()) return false;
    if(!searchData()) return false;
    return true;
}
//===============================================
bool GModuleMap::onNextModuleMap() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    return true;
}
//===============================================
bool GModuleMap::onAddModuleMap() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
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
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_position == 0) {GERROR_ADD(eGERR, "Vous devez sélectionner une donnée."); return false;}
    if(!loadPositionUp()) {GERROR_ADD(eGERR, "Impossible de déplacer vers le haut."); return false;}
    if(!updatePositionUp()) {GSAVE_KO(); return false;}
    if(!loadData()) return false;
    return true;
}
//===============================================
bool GModuleMap::onMoveDownModuleMap() {
    if(m_module->getId() == 0) {GERROR_ADD(eGERR, "L'identifiant du module est obligatoire."); return false;}
    if(m_position == 0) {GERROR_ADD(eGERR, "Vous devez sélectionner une donnée."); return false;}
    if(!loadPositionDown()) {GERROR_ADD(eGERR, "Impossible de déplacer vers le bas."); return false;}
    if(!updatePositionDown()) {GSAVE_KO(); return false;}
    if(!loadData()) return false;
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
bool GModuleMap::searchData() {
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
        lObj->m_id = lRow.at(j++).toInt();
        lObj->m_position = lRow.at(j++).toInt();
        m_map.push_back(lObj);
    }
    m_dataOffset += m_dataSize;
    m_hasData = true;
    if(m_dataOffset >= m_dataCount) m_hasData = false;
    if(m_hasData) {
        GModuleMap* lObj = (GModuleMap*)m_map.back();
        m_lastId = lObj->m_id;
    }
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
            "", m_module->getId()
    ));
    clearMap(m_map);
    for(int i = 0; i < (int)lDataMap.size(); i++) {
        GRow lDataRow = lDataMap.at(i);
        int j = 0;
        GModuleMap* lObj = new GModuleMap;
        lObj->m_id = lDataRow.at(j++).toInt();
        lObj->m_position = lDataRow.at(j++).toInt();
        m_map.push_back(lObj);
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
            "", m_module->getId()
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
            , m_module->getId()
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
            , m_module->getId()
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
            , m_module->getId()
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
            , m_module->getId()
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
            "", m_module->getId()
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
            "", m_module->getId()
            , m_position
    ))) return false;
    return true;
}
//===============================================
bool GModuleMap::insertData() {
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module_map "
            " ( _module_id, _position ) "
            " values ( %d, %d ) "
            "", m_module->getId()
            , m_position
    ))) return false;
    m_id = lMySQL.getId();
    return true;
}
//===============================================
