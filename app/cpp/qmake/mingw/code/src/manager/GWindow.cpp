//===============================================
#include "GWindow.h"
#include "ui_GWindow.h"
#include "GLog2.h"
#include "GPath2.h"
#include "GFile3.h"
#include "GBase64.h"
#include "GOption.h"
#include "GConnection.h"
#include "GModules.h"
//===============================================
GWindow::GWindow(QWidget* _parent)
: QMainWindow(_parent)
, ui(new Ui::GWindow){
    ui->setupUi(this);
    m_file = new GFile3;
    m_modules = new GModules;
}
//===============================================
GWindow::~GWindow() {
    delete m_file;
    delete m_modules;
}
//===============================================
// connection
//===============================================
void GWindow::on_actionStartConnection_triggered() {
    GLOGT(eGFUN, "");
    if(!GCONNECT->isConnect()) {
        GCONNECT->setPseudo("admin");
        GCONNECT->setPassword("password");
        GCONNECT->runConnection();
    }
    else {
        GERROR_ADD(eGERR, "Vous êtes déjà connectés.");
    }
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionStartDisconnection_triggered() {
    GLOGT(eGFUN, "");
    if(GCONNECT->isConnect()) {
        GCONNECT->runDisconnection();
    }
    else {
        GERROR_ADD(eGERR, "Vous êtes déjà déconnectés.");
    }
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
// account
//===============================================
void GWindow::on_actionCreateAccount_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionSearchAccount_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionEnableAccount_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDisableAccount_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionUpdateAccount_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDeleteAccount_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
// group
//===============================================
void GWindow::on_actionCreateGroup_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionSearchGroup_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionUpdateGroup_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDeleteGroup_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
// file
//===============================================
void GWindow::on_actionSaveFile_triggered() {
    GLOGT(eGFUN, "");
    GString lFullname(GPATH("pdf", "mon_fichier_send.pdf"));
    m_file->setFullname(lFullname);
    GString lDataBin(m_file->getContentBin());
    GString lData64(GBase64(lDataBin).encodeData());
    m_file->setFilename(lFullname.getFilename());
    m_file->setContent(lData64);
    m_file->saveFile();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionSearchFile_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDownloadFile_triggered() {
    GLOGT(eGFUN, "");
    GString lFullname(GPATH("pdf", "mon_fichier_recv.pdf"));
    GFile3 lFile(lFullname);
    lFile.setId(1);
    lFile.downloadFile();
    GString lData64(lFile.getContent());
    GString lDataBin(GBase64(lData64).decodeData());
    lFile.setContentBin(lDataBin);
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDeleteFile_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
// module
//===============================================
void GWindow::on_actionCreateModule_triggered() {
    GLOGT(eGFUN, "");
    m_modules->setName("mysql");
    m_modules->createModule();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionSearchModule_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionUpdateModule_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDeleteModule_triggered() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
// options
//===============================================
void GWindow::on_actionCreateOption_triggered() {
    GOption lOption;
    lOption.setName("enable_logs");
    lOption.createOption();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionSearchOption_triggered() {
    GOption lOption;
    lOption.setName("enable_log");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionEnableOption_triggered() {
    GOption lOption;
    lOption.setName("enable_logs");
    lOption.enableOption();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDisableOption_triggered() {
    GOption lOption;
    lOption.setName("enable_logs");
    lOption.disableOption();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionReadOption_triggered() {
    GOption lOption;
    lOption.setName("enable_logs");
    lOption.readOption();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionUpdateOption_triggered() {
    GOption lOption;
    lOption.setName("enable_logs");
    lOption.setState(true);
    lOption.updateOption();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
void GWindow::on_actionDeleteOption_triggered() {
    GOption lOption;
    lOption.setName("enable_logs");
    lOption.deleteOption();
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
