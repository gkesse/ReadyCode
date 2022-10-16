//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
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
void GModuleMap::saveModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "save_module_map", lData);
    deserialize(lData);
}
//===============================================
void GModuleMap::searchModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "search_module_map", lData);
    deserialize(lData);
}
//===============================================
void GModuleMap::deleteModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "delete_module_map", lData);
    deserialize(lData);
}
//===============================================
void GModuleMap::onNextData() {
    clearMap(m_map);
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "search_next_module_map", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleMap::showList() {
    if(m_map.size() == 0) {
        setModuleMap(GModuleMap());
        if(!GLOGI->hasErrors()) {
            GSEARCH_AVOID();
        }
        return false;
    }
    else if(m_map.size() == 1) {
        setModuleMap(0);
        return true;
    }
    m_tableWidget->setWindowTitle("Liste des données par module");
    m_tableWidget->setSize(m_map.size(), 3);
    m_tableWidget->setHeader(0, "id");
    m_tableWidget->setHeader(1, "module");
    m_tableWidget->setHeader(2, "position");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleMap* lModuleMap = (GModuleMap*)m_map.at(i);
        int lId = lModuleMap->m_id;
        m_tableWidget->setData(i, 0, lId, lModuleMap->m_id);
        m_tableWidget->setData(i, 1, lId, m_module->getName());
        m_tableWidget->setData(i, 2, lId, lModuleMap->m_position);
    }
    clearMap(m_map);
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();
    if(lOk == QDialog::Accepted) {
        m_id = m_tableWidget->getKey().toInt();
        setSearch(GSearch());
        searchModuleMap();
        setModuleMap(0);
    }
    return true;
}
//===============================================
bool GModuleMap::showNextList() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleMap* lModuleMap = (GModuleMap*)m_map.at(i);
        int lId = lModuleMap->m_id;
        m_tableWidget->addRow();
        m_tableWidget->addCol(0, lId, lModuleMap->m_id);
        m_tableWidget->addCol(1, lId, lModuleMap->m_position);
    }
    clearMap(m_map);
    return true;
}
//===============================================
