//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTreeWidgetUi.h"
#include "GTreeWidget.h"
//===============================================
GModuleMap::GModuleMap(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_position = 0;
    m_treeWidgetUi = new GTreeWidgetUi;
    m_module = new GModule;
}
//===============================================
GModuleMap::~GModuleMap() {
    delete m_treeWidgetUi;
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
        GModuleMap* lObj = (GModuleMap*)m_map.at(_index);
        setModuleMap(lObj);
    }
    clearMap(m_map);
}
//===============================================
void GModuleMap::setModule(const GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleMap::setModule(const std::shared_ptr<GModule>& _module) {
    m_module->setModule(_module.get());
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
void GModuleMap::searchModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "search_module_map", lData);
    deserialize(lData);
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

    GTreeWidget* lTreeWidget = m_treeWidgetUi->getTreeWidget();
    m_treeWidgetUi->setWindowTitle("Liste des données par module");

    lTreeWidget->clear();
    lTreeWidget->setColumnCount(2);
    lTreeWidget->addHeader();
    lTreeWidget->setData(0, "", "module");
    lTreeWidget->setData(1, "", "node[id]");

    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleMap* lObj = (GModuleMap*)m_map.at(i);
        GString lKey = lObj->serialize();
        lTreeWidget->addRoot();
        lTreeWidget->setData(0, lKey, m_module->getName());
        lTreeWidget->setData(1, lKey, GFORMAT("node[%d]", lObj->getId()));
        if(lKey == lTreeWidget->getKey()) {
            lTreeWidget->selectItem();
        }
    }

    m_treeWidgetUi->setSearch(this);
    int lOk = m_treeWidgetUi->exec();
    if(lOk == QDialog::Accepted) {
        GModuleMap lObj;
        lObj.deserialize(lTreeWidget->getKey());
        setModuleMap(lObj);
    }
    return true;
}
//===============================================
