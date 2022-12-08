//===============================================
#include "GModuleNode.h"
#include "GModule.h"
#include "GModuleType.h"
#include "GModuleKey.h"
#include "GCode.h"
#include "GLog.h"
#include "GMap.h"
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
    m_module.reset(new GModule);
    m_moduleKey.reset(new GModuleKey);
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
    lDom.addData(_code, m_map, this);
    lDom.addData(m_module->serialize(), this);
    lDom.addData(m_moduleKey->serialize(), this);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GModuleNode::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_moduleKey->deserialize(_data);
    m_module->deserialize(_data);
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
void GModuleNode::setModuleNode(const GModuleNode& _moduleNode) {
    m_id = _moduleNode.m_id;
    m_moduleId = _moduleNode.m_moduleId;
    m_mapId = _moduleNode.m_mapId;
    m_keyId = _moduleNode.m_keyId;
    m_value = _moduleNode.m_value;
}
//===============================================
void GModuleNode::setModuleNode(GModuleNode* _moduleNode) {
    setModuleNode(*_moduleNode);
}
//===============================================
void GModuleNode::setModuleNode(int _index) {
    if(_index >= 0 && _index < (int)m_map.size()) {
        GModuleNode* lObj = (GModuleNode*)m_map.at(_index);
        setModuleNode(lObj);
    }
    clearMap(m_map);
}
//===============================================
void GModuleNode::setModule(const GModule& _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleNode::setModule(GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleNode::setModule(const std::shared_ptr<GModule>& _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleNode::setModuleKey(const std::shared_ptr<GModuleKey>& _moduleKey) {
    if(!_moduleKey.get()) return;
    m_moduleKey.reset(new GModuleKey);
    m_moduleKey->deserialize(_moduleKey->serialize());

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
void GModuleNode::loadModuleNode(GFormLayout* _formLayout) {
    if(!m_moduleKey.get()) return;
    std::shared_ptr<GModuleType>& lModuleType = m_moduleKey->getModuleType();
    _formLayout->clear();
    for(int i = 0; i < m_moduleKey->size(); i++) {
        GModuleKey* lObj = (GModuleKey*)m_moduleKey->at(i);
        GModuleType* lObj2 = (GModuleType*)lModuleType->at(i);
        GString lKey = lObj->getName();
        GString lLabel = GFORMAT("%s :", lObj->getLabel().c_str());
        GString lType = lObj2->getName();
        _formLayout->addRow(lKey, lLabel, lType);
    }
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
void GModuleNode::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "search_next_module_key", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleNode::showList() {
    if(m_map.size() == 0) return true;
    if(m_map.size() == 1) {
        setModuleNode(0);
        return true;
    }

    m_tableWidget->setWindowTitle("Liste des données par module");
    m_tableWidget->setSize(m_map.size(), 3);
    m_tableWidget->setHeader(0, "module");
    m_tableWidget->setHeader(1, "nom");
    m_tableWidget->setHeader(2, "libellé");
    m_tableWidget->setHeader(3, "type");

    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleNode* lObj = (GModuleNode*)m_map.at(i);
        GModuleType* lObj2 = (GModuleType*)m_moduleKey->at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->setData(i, 0, lKey, m_module->getName());
        m_tableWidget->setData(i, 3, lKey, lObj2->getName());
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        GModuleNode lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setModuleNode(lObj);
    }
    return true;
}
//===============================================
bool GModuleNode::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleNode* lObj = (GModuleNode*)m_map.at(i);
        GString lKey = lObj->serialize();
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lKey, m_module->getName());
    }
    clearMap(m_map);
    return true;
}
//===============================================
