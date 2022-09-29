//===============================================
#include "GWindow.h"
#include "ui_GWindow.h"
#include "GLog2.h"
#include "GFile3.h"
#include "GBase64.h"
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
    GFile3 lFile3;
    lFile.setFullname("C:\\Users\\tiaka\\Downloads\\eTools\\eDoc\\bryan\\bryan_lettre_absence.pdf");
    lFile2.setFullname("C:\\Users\\tiaka\\Downloads\\eTools\\eDoc\\bryan\\bryan_lettre_absence_2.pdf");
    lFile3.setFullname("C:\\Users\\tiaka\\Downloads\\eTools\\eDoc\\bryan\\bryan_lettre_absence_3.pdf");
    GString lDataBin(lFile.getContentBin());
    GLOGT2(eGMSG, GFORMAT("size : %d", lDataBin.size()));
    lFile2.setContentBin(lDataBin);
    lFile.setFilename("mon_fichier.pdf");
    GString lData64 = GBase64(lDataBin).encodeData();
    lDataBin = GBase64(lData64).decodeData();
    lFile3.setContentBin(lDataBin);
    lFile.setContent("9nV/c8R5A9y1o/+X+XX177r7x9lJgDY/jPPf2X7ZP+M7RF28CtrQHQH3Rtj3n76r9Vn4YWPMVAHrx/L69e6");
    lFile.saveFile();
}
//===============================================
void GWindow::on_actionTelechargerFichier_triggered() {
    GLOGT2(eGFUN, "");
}
//===============================================
