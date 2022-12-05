//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTreeWidgetUi.h"
#include "GTreeWidget.h"
#include "GFormLayout.h"
#include "GModuleKey.h"
//===============================================
GModuleMap::GModuleMap(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
    m_keyId = 0;
    m_position = 0;
    m_treeWidgetUi.reset(new GTreeWidgetUi);
    m_module.reset(new GModule);
    m_moduleKey.reset(new GModuleKey);
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
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "key_id", m_keyId);
    lDom.addData(_code, "position", m_position);
    lDom.addData(_code, "value", m_value);
    lDom.addData(_code, m_map, this);
    lDom.addData(m_module->serialize(), this);
    lDom.addData(GSearch::serialize(), this);
    resetOnlyObjectCopied();
    return lDom.toString();
}
//===============================================
bool GModuleMap::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_module->deserialize(_data);
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
void GModuleMap::setModuleMap(const GModuleMap& _moduleMap) {
    m_id = _moduleMap.m_id;
    m_moduleId = _moduleMap.m_moduleId;
    m_keyId = _moduleMap.m_keyId;
    m_position = _moduleMap.m_position;
    m_value = _moduleMap.m_value;
}
//===============================================
void GModuleMap::setModuleMap(GModuleMap* _moduleMap) {
    setModuleMap(*_moduleMap);
}
//===============================================
void GModuleMap::setModuleMap(const std::shared_ptr<GModuleMap>& _moduleMap) {
    setModuleMap(*_moduleMap);
}
//===============================================
void GModuleMap::setModuleMap(GFormLayout* _formLayout) {
    if(!m_moduleKey.get()) return;
    for(int i = 0; i < m_moduleKey->size(); i++) {
        GModuleMap* lObj = new GModuleMap;
        GModuleKey* lObj2 = (GModuleKey*)m_moduleKey->at(i);
        lObj->m_value = _formLayout->getData(lObj2->getName());
        m_map.push_back(lObj);
    }
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
void GModuleMap::setModule(GModule* _module) {
    m_module->setModule(_module);
}
//===============================================
void GModuleMap::setModule(const std::shared_ptr<GModule>& _module) {
    m_module->setModule(_module.get());
}
//===============================================
void GModuleMap::setModuleKey(const std::shared_ptr<GModuleKey>& _moduleKey) {
    if(!_moduleKey.get()) return;
    m_moduleKey.reset(new GModuleKey);
    m_moduleKey->deserialize(_moduleKey->serialize());
}
//===============================================
void GModuleMap::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleMap::setModuleId(int _moduleId) {
    m_moduleId = _moduleId;
}
//===============================================
void GModuleMap::setKeyId(int _keyId) {
    m_keyId = _keyId;
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
int GModuleMap::getModuleId() const {
    return m_moduleId;
}
//===============================================
int GModuleMap::getKeyId() const {
    return m_keyId;
}
//===============================================
int GModuleMap::getPosition() const {
    return m_position;
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
void GModuleMap::nextModuleMap() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_map", "next_module_map", lData);
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

    m_treeWidgetUi->setWindowTitle("Liste des données par module");
    showList(m_treeWidgetUi);

    m_treeWidgetUi->setSearch(this);
    int lOk = m_treeWidgetUi->exec();

    if(lOk == QDialog::Accepted) {
        GModuleMap lObj;
        lObj.deserialize(m_treeWidgetUi->getKey());
        setModuleMap(lObj);
    }
    return true;
}
//===============================================
bool GModuleMap::showList(std::shared_ptr<GTreeWidgetUi>& _treeWidgetUi) {
    GTreeWidget* lTreeWidget = _treeWidgetUi->getTreeWidget();
    lTreeWidget->clear();
    lTreeWidget->setColumnCount(2);
    lTreeWidget->addHeader();
    lTreeWidget->setData(0, "", "cle");
    lTreeWidget->setData(1, "", "valeur");

    for(int i = 0; i < (int)m_map.size(); i++) {
        GModuleMap* lObj = (GModuleMap*)m_map.at(i);
        lObj->setOnlyObjectCopied();
        GString lKey = lObj->serialize();
        lTreeWidget->addRoot();
        lTreeWidget->setData(1, lKey, lObj->getId());

        if(lKey == _treeWidgetUi->getKey()) {
            lTreeWidget->selectItem();
        }

        for(int j = 0; j < 5; j++) {
            lTreeWidget->addChild();
            lTreeWidget->setData(0, lKey, "cle");
            lTreeWidget->setData(1, lKey, "valeur");
        }
    }

    clearMap(m_map);
    return true;
}
//===============================================
void GModuleMap::onNextData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->setModule(m_module);
    lObj->nextModuleMap();
    lObj->setOnlyObjectCopied();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
void GModuleMap::onAddData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->setModule(m_module);
    lObj->addModuleMap();
    lObj->setOnlyObjectCopied();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
void GModuleMap::onMoveUpData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->setModule(m_module);
    lObj->moveUpModuleMap();
    lObj->setOnlyObjectCopied();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
void GModuleMap::onMoveDownData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->setModule(m_module);
    lObj->moveDownModuleMap();
    lObj->setOnlyObjectCopied();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
