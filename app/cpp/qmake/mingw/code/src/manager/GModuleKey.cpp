//===============================================
#include "GModuleKey.h"
#include "GModule.h"
#include "GModuleType.h"
#include "GCode.h"
#include "GLog.h"
#include "GClient.h"
#include "GTableWidgetUi.h"
#include "GFormLayout.h"
//===============================================
GModuleKey::GModuleKey(const GString& _code)
: GSearch(_code) {
    m_id = 0;
    m_moduleId = 0;
    m_typeId = 0;
    m_tableWidget.reset(new GTableWidgetUi);
}
//===============================================
GModuleKey::~GModuleKey() {
    clearMap();
}
//===============================================
GObject* GModuleKey::clone() const {
    return new GModuleKey;
}
//===============================================
GString GModuleKey::serialize(const GString& _code) {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "module_id", m_moduleId);
    lDom.addData(_code, "type_id", m_typeId);
    lDom.addData(_code, "name", m_name);
    lDom.addData(_code, "label", m_label);
    lDom.addData(_code, "type", m_type.toBase64(), true);
    lDom.addData(_code, "module", m_module.toBase64(), true);
    lDom.addData(_code, m_map, this);
    lDom.addData(GSearch::serialize(), this);
    return lDom.toString();
}
//===============================================
bool GModuleKey::deserialize(const GString& _data, const GString& _code) {
    GSearch::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_moduleId = lDom.getData(_code, "module_id").toInt();
    m_typeId = lDom.getData(_code, "type_id").toInt();
    m_name = lDom.getData(_code, "name");
    m_label = lDom.getData(_code, "label");
    m_type = lDom.getData(_code, "type").fromBase64();
    m_module = lDom.getData(_code, "module").fromBase64();
    lDom.getData(_code, m_map, this);
    return true;
}
//===============================================
void GModuleKey::setModuleKey(const GModuleKey& _moduleKey) {
    m_id = _moduleKey.m_id;
    m_moduleId = _moduleKey.m_moduleId;
    m_typeId = _moduleKey.m_typeId;
    m_name = _moduleKey.m_name;
    m_label = _moduleKey.m_label;
    m_type = _moduleKey.m_type;
    m_module = _moduleKey.m_module;
}
//===============================================
void GModuleKey::setModuleKey(GModuleKey* _moduleKey) {
    setModuleKey(*_moduleKey);
}
//===============================================
void GModuleKey::setModuleKey(int _index) {
    GModuleKey* lObj = (GModuleKey*)at(_index);
    setModuleKey(lObj);
    clearMap();
}
//===============================================
void GModuleKey::writeKeyFormModuleNode(GFormLayout* _formLayout) {
    _formLayout->clear();
    for(int i = 0; i < size(); i++) {
        GModuleKey* lKey = (GModuleKey*)at(i);
        GModuleType lType;
        lType.deserialize(lKey->getType());
        GString lLabel = GFORMAT("%s :", lKey->getLabel().c_str());
        _formLayout->addRow(lKey->getName(), lLabel, lType.getName());
    }
}
//===============================================
void GModuleKey::setId(int _id) {
    m_id = _id;
}
//===============================================
void GModuleKey::setModuleId(int _moduleId) {
    m_moduleId = _moduleId;
}
//===============================================
void GModuleKey::setTypeId(int _typeId) {
    m_typeId = _typeId;
}
//===============================================
void GModuleKey::setName(const GString& _name) {
    m_name = _name;
}
//===============================================
void GModuleKey::setLabel(const GString& _label) {
    m_label = _label;
}
//===============================================
int GModuleKey::getId() const {
    return m_id;
}
//===============================================
int GModuleKey::getModuleId() const {
    return m_moduleId;
}
//===============================================
int GModuleKey::getTypeId() const {
    return m_typeId;
}
//===============================================
GString GModuleKey::getName() const {
    return m_name;
}
//===============================================
GString GModuleKey::getLabel() const {
    return m_label;
}
//===============================================
GString GModuleKey::getType() const {
    return m_type;
}
//===============================================
GString GModuleKey::getModule() const {
    return m_module;
}
//===============================================
void GModuleKey::loadModuleKey() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "load_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleKey::saveModuleKey() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "save_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleKey::searchModuleKey() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "search_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleKey::deleteModuleKey() {
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "delete_module_key", lData);
    deserialize(lData);
}
//===============================================
void GModuleKey::onNextData() {
    clearMap();
    GString lData = serialize();
    lData = GCALL_SERVER("module_key", "search_next_module_key", lData);
    deserialize(lData);
    showNextList();
}
//===============================================
bool GModuleKey::showList() {
    if(size() == 0) return true;
    if(size() == 1) {
        setModuleKey(0);
        return true;
    }

    m_tableWidget->setWindowTitle("Liste des données");
    m_tableWidget->setSize(size(), 3);
    m_tableWidget->setHeader(0, "module");
    m_tableWidget->setHeader(1, "nom");
    m_tableWidget->setHeader(2, "libellé");
    m_tableWidget->setHeader(3, "type");

    for(int i = 0; i < size(); i++) {
        GModuleKey* lKey2 = (GModuleKey*)at(i);
        GModule lModule;
        GModuleType lType;
        lModule.deserialize(lKey2->getModule());
        lType.deserialize(lKey2->getType());
        GString lKey = lKey2->serialize();
        m_tableWidget->setData(i, 0, lKey, lModule.getName());
        m_tableWidget->setData(i, 1, lKey, lKey2->m_name);
        m_tableWidget->setData(i, 2, lKey, lKey2->m_label);
        m_tableWidget->setData(i, 3, lKey, lType.getName());
    }

    clearMap();
    m_tableWidget->setSearch(this);
    int lOk = m_tableWidget->exec();

    if(lOk == QDialog::Accepted) {
        GModuleKey lObj;
        lObj.deserialize(m_tableWidget->getKey());
        setModuleKey(lObj);
    }
    return true;
}
//===============================================
bool GModuleKey::showNextList() {
    for(int i = 0; i < size(); i++) {
        GModuleKey* lKey2 = (GModuleKey*)at(i);
        GModule lModule;
        GModuleType lType;
        lModule.deserialize(lKey2->getModule());
        lType.deserialize(lKey2->getType());
        GString lKey = lKey2->serialize();
        m_tableWidget->addRow();
        m_tableWidget->setData(i, 0, lKey, lModule.getName());
        m_tableWidget->setData(i, 1, lKey, lKey2->m_name);
        m_tableWidget->setData(i, 2, lKey, lKey2->m_label);
        m_tableWidget->setData(i, 3, lKey, lType.getName());
    }
    clearMap();
    return true;
}
//===============================================
