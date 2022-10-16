//===============================================
#include "GLog.h"
#include "GModuleUi.h"
#include "ui_GModuleUi.h"
#include "GModule.h"
#include "GModuleData.h"
#include "GModuleMap.h"
//===============================================
GModuleUi::GModuleUi(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GModuleUi){
    ui->setupUi(this);
    m_module = new GModule;
    m_moduleData = new GModuleData;
    m_moduleMap = new GModuleMap;
    m_isVisibleTabData = false;
    m_isVisibleTabMap = false;
    m_tabDataIndex = ui->tabWidget->indexOf(ui->tabData);
    m_tabMapIndex = ui->tabWidget->indexOf(ui->tabMap);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabVisible(m_tabDataIndex, m_isVisibleTabData);
    ui->tabWidget->setTabVisible(m_tabMapIndex, m_isVisibleTabMap);
    setAttribute(Qt::WA_DeleteOnClose);
    loadModuleMap();
}
//===============================================
GModuleUi::~GModuleUi() {
    delete m_module;
    delete m_moduleData;
    delete m_moduleMap;
}
//===============================================
void GModuleUi::readData() {
    m_module->setName(ui->edtName->text());
    m_moduleData->setName(ui->edtNameData->text());
    m_moduleData->setValue(ui->edtValueData->text());
    //m_moduleMap->setPosition(GString(0).toInt());
}
//===============================================
void GModuleUi::writeData() {
    m_isVisibleTabData = (m_module->getId() != 0);
    m_isVisibleTabMap = (m_module->getId() != 0);
    ui->edtName->setText(m_module->getName().c_str());
    ui->edtNameData->setText(m_moduleData->getName().c_str());
    ui->edtValueData->setText(m_moduleData->getValue().c_str());
    //ui->edtPositionMap->setText(GString(0).c_str());
    ui->tabWidget->setTabVisible(m_tabDataIndex, m_isVisibleTabData);
    ui->tabWidget->setTabVisible(m_tabMapIndex, m_isVisibleTabMap);
}
//===============================================
void GModuleUi::loadModuleMap() {
    GLOGT(eGFUN, "");
    m_moduleMap->loadModuleMap();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module
//===============================================
void GModuleUi::on_btnSave_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_module->saveModule();
    if(GLOGI->hasErrors()) {
        m_module->setModule(0);
    }
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnSearch_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_module->setSearch(GSearch());
    m_module->searchModule();
    m_module->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnNew_clicked() {
    GLOGT(eGFUN, "");
    m_module->setModule(GModule());
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module_data
//===============================================
void GModuleUi::on_btnSaveData_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleData->setModule(m_module);
    m_moduleData->saveModuleData();
    if(GLOGI->hasErrors()) {
        m_module->setModule(0);
    }
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnSearchData_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleData->setModule(m_module);
    m_moduleData->setSearch(GSearch());
    m_moduleData->searchModuleData();
    m_moduleData->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnNewData_clicked() {
    GLOGT(eGFUN, "");
    m_moduleData->setModuleData(GModuleData());
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// module_map
//===============================================
void GModuleUi::on_btnAddMap_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_moduleMap->setModule(m_module);
    m_moduleMap->addModuleMap();
    if(GLOGI->hasErrors()) {
        m_moduleMap->setModuleMap(0);
    }
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnSaveMap_clicked() {

}
//===============================================
void GModuleUi::on_btnSearchMap_clicked() {

}
//===============================================
void GModuleUi::on_btnNewMap_clicked() {

}
//===============================================
