//===============================================
#include "GModuleMap.h"
#include "GModule.h"
#include "GModuleNode.h"
#include "GModuleType.h"
#include "GModuleKey.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTreeWidgetUi.h"
#include "GTreeWidget.h"
#include "GFormLayout.h"
//===============================================
GModuleMap::GModuleMap(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
    m_position = 0;
    m_module.reset(new GModule);
    m_moduleNode.reset(new GModuleNode);
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
    lDom.addData(_code, m_map, this);
    lDom.addData(m_module->serialize(), this);
    lDom.addData(m_moduleNode->serialize(), this);
    lDom.addData(GSearch::serialize(), this);
    resetOnlyObjectCopied();
    return lDom.toString();
}
//===============================================
bool GModuleMap::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    m_moduleNode->deserialize(_data);
    m_module->deserialize(_data);
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
void GModuleMap::setModuleMap(const GModuleMap& _moduleMap) {
    m_id = _moduleMap.m_id;
    m_moduleId = _moduleMap.m_moduleId;
    m_position = _moduleMap.m_position;
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
void GModuleMap::setModuleMap(int _index) {
    if(_index < (int)m_map.size()) {
        GModuleMap* lObj = (GModuleMap*)at(_index);
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
void GModuleMap::setModuleNode(const std::shared_ptr<GModuleNode>& _moduleNode) {
    if(!_moduleNode.get()) return;
    m_moduleNode.reset(new GModuleNode);
    m_moduleNode->deserialize(_moduleNode->serialize());
}
//===============================================
void GModuleMap::readFormModuleNode(GFormLayout* _formLayout) {
    if(!m_moduleNode.get()) return;
    std::shared_ptr<GModuleKey>& lModuleKey = m_moduleNode->getModuleKey();
    std::shared_ptr<GModuleType>& lModuleType = lModuleKey->getModuleType();
    for(int i = 0; i < lModuleKey->size(); i++) {
        GModuleNode* lObj = new GModuleNode;
        GModuleKey* lObj2 = (GModuleKey*)lModuleKey->at(i);
        GModuleType* lObj3 = (GModuleType*)lModuleType->at(i);
        int lId = _formLayout->getId(lObj2->getName()).toInt();
        lObj->setId(lId);
        lObj->setModuleId(m_moduleId);
        lObj->setMapId(m_id);
        lObj->setKeyId(lObj2->getId());
        lObj->setValue(_formLayout->getData(lObj2->getName(), lObj3->getName()));
        m_moduleNode->add(lObj);
    }
}
//===============================================
void GModuleMap::writeFormModuleNode(GFormLayout* _formLayout) {
    if(!m_moduleNode.get()) return;
    std::shared_ptr<GModuleKey>& lModuleKey = m_moduleNode->getModuleKey();
    std::shared_ptr<GModuleType>& lModuleType = lModuleKey->getModuleType();
    for(int i = 0; i < m_moduleNode->size(); i++) {
        GModuleNode* lObj = (GModuleNode*)m_moduleNode->at(i);
        GModuleKey* lObj2 = (GModuleKey*)lModuleKey->at(i);
        GModuleType* lObj3 = (GModuleType*)lModuleType->at(i);
        int lId = lObj->getId();
        GString lKey = lObj2->getName();
        GString lType = lObj3->getName();
        GString lValue = lObj->getValue();
        _formLayout->setData(lKey, lValue, lType);
        _formLayout->setId(lKey, lId);
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
    m_moduleNode->clearMap();
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

        if(lKey == _treeWidgetUi->getKey()) {
            lTreeWidget->selectItem();
        }

        GModuleNode lNode;
        lNode.deserialize(lObj->getNode());

        for(int j = 0; j < lNode.size(); j++) {
            GModuleNode* lObj2 = (GModuleNode*)lNode.at(j);
            GModuleKey lObj3;
            lObj3.deserialize(lObj2->getKey());
            qDebug() << "##############" << lObj3.serialize().c_str();
            lTreeWidget->addChild();
            lTreeWidget->setData(0, lKey, lObj3.getName());
            lTreeWidget->setData(1, lKey, lObj2->getValue());
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
