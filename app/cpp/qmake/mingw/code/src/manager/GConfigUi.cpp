//===============================================
#include "GConfigUi.h"
#include "ui_GConfigUi.h"
#include "GLog.h"
#include "GModule2.h"
//===============================================
GConfigUi::GConfigUi(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GConfigUi){
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GConfigUi::~GConfigUi() {

}
//===============================================
void GConfigUi::readData() {
    m_module.reset(new GModule2);
    // module
    m_module->setName(ui->edtNameModule->text());
}
//===============================================
void GConfigUi::writeData() {
    // module
    ui->edtNameModule->setText(m_module->getName().c_str());
}
//===============================================
void GConfigUi::on_btnSaveModule_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_module->saveModule();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GConfigUi::on_btnSearchModule_clicked() {
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
void GConfigUi::on_btnNewModule_clicked() {
    GLOGT(eGFUN, "");
    m_module.reset(new GModule2);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
