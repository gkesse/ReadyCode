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
    GFile3 lFile2;
    lFile.setFullname("C:\\Users\\tiaka\\Downloads\\eTools\\eDoc\\bryan\\bryan_lettre_absence.pdf");
    lFile2.setFullname("C:\\Users\\tiaka\\Downloads\\eTools\\eDoc\\bryan\\bryan_lettre_absence_2.pdf");
    lFile2.setContentBin(lFile.getContentBin());
    lFile.setFilename("mon_fichier.pdf");
    lFile.setContent("mon_fichier.pdf");
    lFile.saveFile();
}
//===============================================
void GWindow::on_actionTelechargerFichier_triggered() {
    GLOGT2(eGFUN, "");
}
//===============================================
