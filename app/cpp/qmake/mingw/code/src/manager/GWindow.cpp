//===============================================
#include "GWindow.h"
#include "ui_GWindow.h"
#include "GLog2.h"
#include "GFile3.h"
#include "GBase64.h"
#include "GOption.h"
#include "GPath2.h"
//===============================================
GWindow::GWindow(QWidget* _parent)
: QMainWindow(_parent)
, ui(new Ui::GWindow){
    ui->setupUi(this);
}
//===============================================
GWindow::~GWindow() {

}
//===============================================
// file
//===============================================
void GWindow::on_actionStartConnection_triggered() {
    GLOGT2(eGFUN, "");

}
//===============================================
// file
//===============================================
void GWindow::on_actionSaveFile_triggered() {
    GLOGT2(eGFUN, "");
    GString lFullname(GPATH("pdf", "mon_fichier_send.pdf"));
    GFile3 lFile(lFullname);
    GString lDataBin(lFile.getContentBin());
    GString lData64(GBase64(lDataBin).encodeData());
    lFile.setFilename(lFullname.getFilename());
    lFile.setContent(lData64);
    lFile.saveFile();
}
//===============================================
void GWindow::on_actionDownloadFile_triggered() {
    GLOGT2(eGFUN, "");
    GString lFullname(GPATH("pdf", "mon_fichier_recv.pdf"));
    GFile3 lFile(lFullname);
    lFile.setId(1);
    lFile.downloadFile();
    GString lData64(lFile.getContent());
    GString lDataBin(GBase64(lData64).decodeData());
    lFile.setContentBin(lDataBin);
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
void GWindow::on_actionSearchOption_triggered() {
    GOption lOption;
    lOption.setName("enable_log");
    GERROR_SHOWG2(eGERR);
    GLOG_SHOWG2(eGLOG);
}
//===============================================
