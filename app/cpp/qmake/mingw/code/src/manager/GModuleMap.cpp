//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
#include "GTreeWidgetUi.h"
//===============================================
GModuleMap::GModuleMap(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_position = 0;
    m_tableWidget = new GTableWidgetUi;
    m_module = new GModule;
}
//===============================================
GModuleMap::~GModuleMap() {
    delete m_tableWidget;
    delete m_module;
    clearMap(m_map);
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
void GModuleMap::setModuleMap(const GModuleMap& _moduleMap) {
    m_id = _moduleMap.m_id;
    m_position = _moduleMap.m_position;
}
//===============================================
void GModuleMap::setModuleMap(GModuleMap* _moduleMap) {
    setModuleMap(*_moduleMap);
}
//===============================================
void GModuleMap::setModuleMap(int _index) {
    if(_index < (int)m_map.size()) {
        GModuleMap* lModules = (GModuleMap*)m_map.at(_index);
        setModuleMap(lModules);
    }
    clearMap(m_map);
}
//===============================================
void GModuleMap::setModule(GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleMap::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleMap::setPosition(int _position) {
    m_position = _position;
}
//===============================================
int GModuleMap::getId() const {
    return m_id;
}
//===============================================
int GModuleMap::getPosition() const {
    return m_position;
}
//===============================================
void GModuleMap::loadModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "load_module_map", lData);
    deserialize(lData);
}
//===============================================
void GModuleMap::addModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "add_module_map", lData);
    deserialize(lData);
}
//===============================================
void GModuleMap::moveUpModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "move_up_module_map", lData);
    deserialize(lData);
}
//===============================================
void GModuleMap::moveDownModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "move_down_module_map", lData);
    deserialize(lData);
}
//===============================================
bool GModuleMap::showModuleMap(GTreeWidgetUi* _treeWidget) {
    _treeWidget->clear();
    _treeWidget->setColumnCount(2);
    _treeWidget->addHeader();
    _treeWidget->setData(0, "", "module");
    _treeWidget->setData(1, "", "node[id]");

    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleMap* lModuleMap = (GModuleMap*)m_map.at(i);
        GString lKey = lModuleMap->serialize();
        _treeWidget->addRoot();
        _treeWidget->setData(0, lKey, m_module->getName());
        _treeWidget->setData(1, lKey, GFORMAT("node[%d]", lModuleMap->getId()));
        if(lKey == _treeWidget->getKey()) {
            _treeWidget->selectItem();
        }
    }
    return true;
}
//===============================================
