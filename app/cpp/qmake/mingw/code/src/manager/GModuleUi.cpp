//===============================================
#include "GLog.h"
#include "GModuleUi.h"
#include "ui_GModuleUi.h"
#include "GModule.h"
#include "GModuleData.h"
//===============================================
GModuleUi::GModuleUi(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GModuleUi){
    ui->setupUi(this);
    m_modules = new GModule;
    m_modulesData = new GModuleData;
    m_tabDataIndex = ui->tabWidget->indexOf(ui->tabData);
    m_isVisibleTabData = false;
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabVisible(m_tabDataIndex, m_isVisibleTabData);
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GModuleUi::~GModuleUi() {
    delete m_modules;
    delete m_modulesData;
}
//===============================================
void GModuleUi::readData() {
    m_modules->setName(ui->edtName->text());
}
//===============================================
void GModuleUi::writeData() {
    m_isVisibleTabData = (m_modules->getId() != 0);
    ui->edtName->setText(m_modules->getName().c_str());
    ui->tabWidget->setTabVisible(m_tabDataIndex, m_isVisibleTabData);
}
//===============================================
void GModuleUi::on_btnSave_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_modules->saveModule();
    if(GLOGI->hasErrors()) {
        m_modules->setModule(0);
    }
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnSearch_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_modules->setSearch(GSearch());
    m_modules->searchModule();
    m_modules->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnNew_clicked() {
    GLOGT(eGFUN, "");
    m_modules->setModule(GModule());
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnSaveData_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_modulesData->setModulesId(m_modules->getId());
    m_modulesData->saveModulesData();
    if(GLOGI->hasErrors()) {
        m_modules->setModule(0);
    }
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnSearchData_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_modules->setSearch(GSearch());
    m_modules->searchModule();
    m_modules->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnNewData_clicked() {
    GLOGT(eGFUN, "");
    m_modules->setModule(GModule());
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
