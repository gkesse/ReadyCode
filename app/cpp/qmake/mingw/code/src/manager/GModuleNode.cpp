//===============================================
#include "GModuleNode.h"
#include "GModule.h"
#include "GModuleType.h"
#include "GModuleKey.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
#include "GFormLayout.h"
//===============================================
GModuleNode::GModuleNode(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
    m_mapId = 0;
    m_keyId = 0;
    m_tableWidget.reset(new GTableWidgetUi);
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
GString GModuleNode::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "map_id", m_mapId);
    lDom.addData(_code, "key_id", m_keyId);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, "key", m_key.toBase64(), true);
    lDom.addData(_code, m_map, this);
    lDom.addData(GSearch::serialize(), this);
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
    m_key = lDom.getData(_code, "key").fromBase64();
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleNode::setModuleNode(const GModuleNode& _moduleNode) {
    m_id = _moduleNode.m_id;
    m_moduleId = _moduleNode.m_moduleId;
    m_mapId = _moduleNode.m_mapId;
    m_keyId = _moduleNode.m_keyId;
    m_value = _moduleNode.m_value;
    m_key = _moduleNode.m_key;
}
//===============================================
void GModuleNode::setModuleNode(GModuleNode* _moduleNode) {
    setModuleNode(*_moduleNode);
}
//===============================================
void GModuleNode::setModuleNode(int _index) {
    GModuleNode* lObj = (GModuleNode*)at(_index);
    setModuleNode(lObj);
    clearMap();
}
//===============================================
GModuleNode* GModuleNode::getData(int _keyId) const {
    for(int i = 0; i < size(); i++) {
        GModuleNode* lObj = (GModuleNode*)at(i);
        if(lObj->getKeyId() == _keyId) {
            return lObj;
        }
    }
    return 0;
}
//===============================================
void GModuleNode::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleNode::setModuleId(int _moduleId) {
    m_moduleId = _moduleId;
}
//===============================================
void GModuleNode::setMapId(int _mapId) {
    m_mapId = _mapId;
}
//===============================================
void GModuleNode::setKeyId(int _keyId) {
    m_keyId = _keyId;
}
//===============================================
void GModuleNode::setValue(const GString& _value) {
    m_value = _value;
}
//===============================================
int GModuleNode::getId() const {
    return m_id;
}
//===============================================
int GModuleNode::getModuleId() const {
    return m_moduleId;
}
//===============================================
int GModuleNode::getMapId() const {
    return m_mapId;
}
//===============================================
int GModuleNode::getKeyId() const {
    return m_keyId;
}
//===============================================
GString GModuleNode::getValue() const {
    return m_value;
}
//===============================================
GString GModuleNode::getKey() const {
    return m_key;
}
//===============================================
void GModuleNode::loadModuleNode() {
    if(m_moduleId <= 0) return;
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "load_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleNode::saveModuleNode() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "save_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleNode::searchModuleNode() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "search_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleNode::deleteModuleNode() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "delete_module_key", lData);
    deserialize(lData);
}
//===============================================
