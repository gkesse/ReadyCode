//===============================================
#include "GLog.h"
#include "GModuleUi.h"
#include "ui_GModuleUi.h"
#include "GModules.h"
//===============================================
GModuleUi::GModuleUi(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GModuleUi){
    ui->setupUi(this);
    m_modules = new GModules;
    m_tabDataIndex = ui->tabWidget->indexOf(ui->tabData);
    m_isVisibleTabData = false;
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabVisible(m_tabDataIndex, m_isVisibleTabData);
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GModuleUi::~GModuleUi() {

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
        m_modules->setModules(0);
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
    m_modules->setModules(GModules());
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
