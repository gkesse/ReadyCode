//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GModuleNode.h"
#include "GModuleType.h"
#include "GModuleKey.h"
#include "GCode.h"
#include "GClient.h"
#include "GTreeWidgetUi.h"
#include "GTreeWidget.h"
#include "GFormLayout.h"
//===============================================
GModuleMap::GModuleMap()
: GSearch() {
    m_id = 0;
    m_moduleId = 0;
    m_position = 0;
    m_treeWidgetUi.reset(new GTreeWidgetUi);
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
GString GModuleMap::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "position", m_position);
    lDom.addData(_code, "node", m_node.toBase64(), true);
    lDom.addData(_code, m_map);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
void GModuleMap::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "module_id").toInt();
    m_position = lDom.getData(_code, "position").toInt();
    m_node = lDom.getData(_code, "node").fromBase64();
    lDom.getData(_code, m_map, this);
}
//===============================================
void GModuleMap::setModuleMap(const GModuleMap& _moduleMap) {
    m_id = _moduleMap.m_id;
    m_moduleId = _moduleMap.m_moduleId;
    m_position = _moduleMap.m_position;
    m_node = _moduleMap.m_node;
}
//===============================================
void GModuleMap::setModuleMap(GModuleMap* _moduleMap) {
    setModuleMap(*_moduleMap);
}
//===============================================
void GModuleMap::setModuleMap(int _index) {
    GModuleMap* lObj = (GModuleMap*)at(_index);
    setModuleMap(lObj);
    clearMap();
}
//===============================================
void GModuleMap::readFormModuleNode(GFormLayout* _formLayout, const std::shared_ptr<GModuleKey>& _moduleKey) {
    GModuleNode lNode;
    for(int i = 0; i < _moduleKey->size(); i++) {
        GModuleKey* lKey = (GModuleKey*)_moduleKey->at(i);
        GModuleType lType;
        lType.deserialize(lKey->getType());
        int lId = _formLayout->getId(lKey->getName()).toInt();
        GModuleNode* lNode2 = new GModuleNode;
        lNode2->setId(lId);
        lNode2->setModuleId(m_moduleId);
        lNode2->setMapId(m_id);
        lNode2->setKeyId(lKey->getId());
        lNode2->setValue(_formLayout->getData(lKey->getName(), lType.getName()));
        lNode.add(lNode2);
    }
    m_node = lNode.serialize();
}
//===============================================
void GModuleMap::writeFormModuleNode(GFormLayout* _formLayout, const std::shared_ptr<GModuleKey>& _moduleKey) {
    GModuleNode lNode;
    lNode.deserialize(m_node);
    for(int i = 0; i < _moduleKey->size(); i++) {
        GModuleKey* lKey = (GModuleKey*)_moduleKey->at(i);
        GModuleNode* lNode2 = lNode.getData(lKey->getId());
        GModuleNode lNode3;
        if(lNode2) lNode3.setModuleNode(lNode2);
        GModuleType lType;
        lType.deserialize(lKey->getType());
        _formLayout->setData(lKey->getName(), lNode3.getValue(), lType.getName());
        _formLayout->setId(lKey->getName(), lNode3.getId());
    }
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
int GModuleMap::getPosition() const {
    return m_position;
}
//===============================================
GString GModuleMap::getNode() const {
    return m_node;
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
    if(size() == 0) return true;
    if(size() == 1) {
        setModuleMap(0);
        return true;
    }

    m_treeWidgetUi->setWindowTitle("Liste des données");
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

    for(int i = 0; i < size(); i++) {
        GModuleMap* lObj = (GModuleMap*)at(i);
        GString lKey = lObj->serialize();
        GString lNoeud = GFORMAT("noeud[%d]", lObj->getPosition());
        lTreeWidget->addRoot();
        lTreeWidget->setData(0, lKey, lNoeud);
        lTreeWidget->setData(1, lKey, "");

        if(lKey == _treeWidgetUi->getKey()) {
            lTreeWidget->selectItem();
        }

        GModuleNode lNode;
        lNode.deserialize(lObj->getNode());

        for(int j = 0; j < lNode.size(); j++) {
            GModuleNode* lNode2 = (GModuleNode*)lNode.at(j);
            GModuleKey lKey2;
            lKey2.deserialize(lNode2->getKey());
            lTreeWidget->addChild();
            lTreeWidget->setData(0, lKey, lKey2.getName());
            lTreeWidget->setData(1, lKey, lNode2->getValue());
        }
    }

    clearMap();
    return true;
}
//===============================================
void GModuleMap::onNextData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->nextModuleMap();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
void GModuleMap::onAddData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->addModuleMap();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
void GModuleMap::onMoveUpData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->moveUpModuleMap();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
void GModuleMap::onMoveDownData() {
    std::shared_ptr<GModuleMap> lObj(new GModuleMap);
    lObj->deserialize(m_treeWidgetUi->getKey());
    lObj->moveDownModuleMap();
    m_treeWidgetUi->setKey(lObj->serialize());
    if(!GLOGI->hasErrors()) {
        lObj->showList(m_treeWidgetUi);
    }
}
//===============================================
