//===============================================
#include "GWindow.h"
#include "ui_GWindow.h"
#include "GLog2.h"
#include "GFile3.h"
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
void GWindow::on_actionEnregistrerFichier_triggered() {
    GFile3 lFile;
    lFile.setKey("fic");
    lFile.setFilename("mon_fichier.pdf");
    lFile.setContent("mon_fichier.pdf");
    lFile.saveFile();
}
//===============================================
void GWindow::on_actionTelechargerFichier_triggered() {
    GLOGT2(eGFUN, "");
}
//===============================================
