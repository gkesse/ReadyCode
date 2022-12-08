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
    m_mapId = 0;
    m_keyId = 0;
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
    lDom.addData(_code, "map_id", m_mapId);
    lDom.addData(_code, "key_id", m_keyId);
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
    m_mapId = lDom.getData(_code, "map_id").toInt();
    m_keyId = lDom.getData(_code, "key_id").toInt();
    m_value = lDom.getData(_code, "value");
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleNode::setMapId(int _mapId) {
    m_mapId = _mapId;
}
//===============================================
bool GModuleNode::insertData() {
    for(int i = 0; i < size(); i++) {
        GModuleNode* lObj = (GModuleNode*)at(i);
        lObj->m_mapId = m_mapId;
        insertData(lObj);
    }
    return true;
}
//===============================================
bool GModuleNode::insertData(GModuleNode* _obj) {
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " insert into _module_node "
            " ( _module_id, _map_id, _key_id, _value ) "
            " values ( %d, %d, %d, '%s' ) "
            "", _obj->m_moduleId
            , _obj->m_mapId
            , _obj->m_keyId
            , _obj->m_value.c_str()
    ))) return false;
    _obj->m_id = lMySQL.getId();
    return true;
}
//===============================================
bool GModuleNode::updateData() {
    for(int i = 0; i < size(); i++) {
        GModuleNode* lObj = (GModuleNode*)at(i);
        lObj->m_mapId = m_mapId;
        updateData(lObj);
    }
    return true;
}
//===============================================
bool GModuleNode::updateData(GModuleNode* _obj) {
    if(m_id == 0) return false;
    GMySQL lMySQL;
    if(!lMySQL.execQuery(GFORMAT(""
            " update _module_node set "
            "   _module_id = %d "
            " , _map_id = %d "
            " , _key_id = %d "
            " , _value = '%s' "
            " where 1 = 1 "
            " and _id = %d "
            "", m_moduleId
            , m_mapId
            , m_keyId
            , m_value.c_str()
    ))) return false;
    return true;
}
//===============================================
