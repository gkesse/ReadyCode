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
    m_moduleId = 0;
    m_moduleDataId = 0;
    m_moduleMapId = 0;

    m_isVisibleTabData = false;
    m_isVisibleTabMap = false;

    m_tabDataIndex = ui->tabWidget->indexOf(ui->tabData);
    m_tabMapIndex = ui->tabWidget->indexOf(ui->tabMap);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabVisible(m_tabDataIndex, m_isVisibleTabData);
    ui->tabWidget->setTabVisible(m_tabMapIndex, m_isVisibleTabMap);
    ui->treeMap->setColumnCount(0);

    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GModuleUi::~GModuleUi() {

}
//===============================================
void GModuleUi::readData() {
    m_module.reset(new GModule);
    m_moduleData.reset(new GModuleData);
    m_moduleMap.reset(new GModuleMap);

    m_module->setId(m_moduleId);
    m_module->setName(ui->edtName->text());
    m_moduleData->setId(m_moduleDataId);
    m_moduleData->setName(ui->edtNameData->text());
    m_moduleData->setValue(ui->edtValueData->text());
}
//===============================================
void GModuleUi::writeData() {
    m_isVisibleTabData = (m_module->getId() != 0);
    m_isVisibleTabMap = (m_module->getId() != 0);

    m_moduleId = m_module->getId();
    ui->edtName->setText(m_module->getName().c_str());
    m_moduleDataId = m_moduleData->getId();
    ui->edtNameData->setText(m_moduleData->getName().c_str());
    ui->edtValueData->setText(m_moduleData->getValue().c_str());
    ui->tabWidget->setTabVisible(m_tabDataIndex, m_isVisibleTabData);
    ui->tabWidget->setTabVisible(m_tabMapIndex, m_isVisibleTabMap);
}
//===============================================
void GModuleUi::loadModuleMap() {
    GLOGT(eGFUN, "");
    if(!m_module->getId()) return;
    m_moduleMap->setModule(m_module.get());
    m_moduleMap->loadModuleMap();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// qtabwidget
//===============================================
void GModuleUi::on_tabWidget_tabBarClicked(int _index) {
    GLOGT(eGFUN, "");
    if(_index == m_tabMapIndex) {
        onTabMap();
    }
}
//===============================================
void GModuleUi::onTabMap() {

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
    loadModuleMap();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnNew_clicked() {
    GLOGT(eGFUN, "");
    m_module.reset(new GModule);
    m_moduleData.reset(new GModuleData);
    m_moduleMap.reset(new GModuleMap);
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
    m_moduleData->setModule(m_module.get());
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
    m_moduleData->setModule(m_module.get());
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
    m_moduleMap->setModule(m_module.get());
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
