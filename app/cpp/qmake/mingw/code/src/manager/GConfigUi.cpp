//===============================================
#include "GConfigUi.h"
#include "ui_GConfigUi.h"
#include "GLog.h"
#include "GModule.h"
#include "GModuleData.h"
#include "GModuleKey.h"
#include "GModuleMap.h"
#include "GModuleType.h"
#include "GModuleNode.h"
//===============================================
GConfigUi::GConfigUi(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GConfigUi){
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    m_moduleId = 0;
    m_moduleDataId = 0;
    m_moduleKeyId = 0;
    m_moduleMapId = 0;
    m_mapPosition = 0;
    m_moduleTypeId = 0;

    onLoadSearchConfig();
    onLoadModuleType();
    onLoadCmbTypeModuleKey();
}
//===============================================
GConfigUi::~GConfigUi() {

}
//===============================================
void GConfigUi::readData() {
    m_module.reset(new GModule);
    m_moduleData.reset(new GModuleData);
    m_moduleKey.reset(new GModuleKey);
    m_moduleMap.reset(new GModuleMap);
    m_moduleType.reset(new GModuleType);
    // module
    m_module->setId(m_moduleId);
    m_module->setName(ui->edtNameModule->text());
    // module_data
    m_moduleData->setId(m_moduleDataId);
    m_moduleData->setModuleId(m_moduleId);
    m_moduleData->setName(ui->edtNameData->text());
    m_moduleData->setValue(ui->edtValueData->text());
    // module_key
    m_moduleKey->setId(m_moduleKeyId);
    m_moduleKey->setModuleId(m_moduleId);
    m_moduleKey->setName(ui->edtNameKey->text());
    m_moduleKey->setLabel(ui->edtLabelKey->text());
    m_moduleKey->setTypeId(ui->cmbTypeKey->currentData().toInt());
    // module_map
    m_moduleMap->setId(m_moduleMapId);
    m_moduleMap->setModuleId(m_moduleId);
    m_moduleMap->setPosition(m_mapPosition);
    // module_type
    m_moduleType->setId(m_moduleTypeId);
    m_moduleType->setName(ui->edtNameType->text());
}
//===============================================
void GConfigUi::writeData() {
    // module
    m_moduleId = m_module->getId();
    ui->edtNameModule->setText(m_module->getName().c_str());
    // module_data
    m_moduleDataId = m_moduleData->getId();
    ui->edtNameData->setText(m_moduleData->getName().c_str());
    ui->edtValueData->setText(m_moduleData->getValue().c_str());
    // module_key
    m_moduleKeyId = m_moduleKey->getId();
    ui->edtNameKey->setText(m_moduleKey->getName().c_str());
    ui->edtLabelKey->setText(m_moduleKey->getLabel().c_str());
    ui->cmbTypeKey->setIndexData(m_moduleKey->getTypeId());
    // module_map
    m_moduleMapId = m_moduleMap->getId();
    m_mapPosition = m_moduleMap->getPosition();
    // module_type
    m_moduleTypeId = m_moduleType->getId();
    ui->edtNameType->setText(m_moduleType->getName().c_str());
}
//===============================================
// module
//===============================================
void GConfigUi::on_btnSaveModule_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_module->saveModule();
    onLoadModuleKey();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSearchModule_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_module->setSearch(m_searchConfig);
    m_module->searchModule();
    m_module->showList();
    onLoadModuleKey();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnNewModule_clicked() {
    GLOGT(eGFUN, "");
    m_module.reset(new GModule);
    m_moduleData.reset(new GModuleData);
    m_moduleKey.reset(new GModuleKey);
    m_moduleMap.reset(new GModuleMap);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module_data
//===============================================
void GConfigUi::on_btnSaveData_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleData->saveModuleData();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSearchData_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleData->setSearch(m_searchConfig);
    m_moduleData->searchModuleData();
    m_moduleData->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnNewData_clicked() {
    GLOGT(eGFUN, "");
    m_moduleData.reset(new GModuleData);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module_key
//===============================================
void GConfigUi::onLoadModuleKey() {
    GLOGT(eGFUN, "");
    m_moduleKeyList.reset(new GModuleKey);
    m_moduleKeyList->setModuleId(m_module->getId());
    m_moduleKeyList->loadModuleKey();
    onLoadKeyModuleNode();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::onLoadCmbTypeModuleKey() {
    GLOGT(eGFUN, "");
    ui->cmbTypeKey->clear();
    ui->cmbTypeKey->addItem("Sélectionner un type...", 0);
    m_moduleTypeList->loadComboBox(ui->cmbTypeKey);
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSaveKey_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleKey->saveModuleKey();
    onLoadModuleKey();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSearchKey_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleKey->setSearch(m_searchConfig);
    m_moduleKey->searchModuleKey();
    m_moduleKey->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnNewKey_clicked() {
    GLOGT(eGFUN, "");
    m_moduleKey.reset(new GModuleKey);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module_map
//===============================================
void GConfigUi::on_btnSaveMap_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleMap->setModuleNode(m_moduleNode);
    m_moduleMap->readFormModuleNode(ui->layModuleMap);
    m_moduleMap->saveModuleMap();
    m_moduleMap->writeFormModuleNode(ui->layModuleMap);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSearchMap_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleMap->setSearch(m_searchConfig);
    m_moduleMap->searchModuleMap();
    m_moduleMap->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnNewMap_clicked() {
    GLOGT(eGFUN, "");
    m_moduleMap.reset(new GModuleMap);
    m_moduleMap->writeFormModuleNode(ui->layModuleMap);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module_node
//===============================================
void GConfigUi::onLoadKeyModuleNode() {
    GLOGT(eGFUN, "");
    m_moduleNode.reset(new GModuleNode);
    m_moduleNode->setModuleKey(m_moduleKeyList);
    m_moduleNode->writeKeyFormModuleNode(ui->layModuleMap);
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module_type
//===============================================
void GConfigUi::onLoadModuleType() {
    GLOGT(eGFUN, "");
    m_moduleTypeList.reset(new GModuleType);
    m_moduleTypeList->loadModuleType();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSaveType_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleType->saveModuleType();
    onLoadModuleType();
    onLoadCmbTypeModuleKey();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSearchType_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleType->setSearch(m_searchConfig);
    m_moduleType->searchModuleType();
    m_moduleType->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnDeleteType_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleType->deleteModuleType();
    m_moduleType.reset(new GModuleType);
    onLoadModuleType();
    onLoadCmbTypeModuleKey();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnNewType_clicked() {
    GLOGT(eGFUN, "");
    m_moduleType.reset(new GModuleType);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// search
//===============================================
void GConfigUi::onLoadSearchConfig() {
    GLOGT(eGFUN, "");
    m_searchConfig.reset(new GSearch);
    m_searchConfig->setDataSize(10);
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
