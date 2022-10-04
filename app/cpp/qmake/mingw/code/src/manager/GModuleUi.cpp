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
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GModuleUi::~GModuleUi() {
    GLOGT(eGFUN, "");
}
//===============================================
void GModuleUi::readData() {
    m_modules->setName(ui->edtName->text());
}
//===============================================
void GModuleUi::writeData() {
    ui->edtName->setText(m_modules->getName().c_str());
}
//===============================================
void GModuleUi::on_btnSave_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_modules->createModule();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnSearch_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_modules->searchModule();
    m_modules->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GModuleUi::on_btnNew_clicked() {
    GLOGT(eGFUN, "");
    m_modules->assign(GModules());
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
