//===============================================
#include "GQtDialog.h"
#include "GQtFindDialog.h"
//===============================================
GQtDialog::GQtDialog(QWidget* _parent) :
QDialog(_parent) {

}
//===============================================
GQtDialog::~GQtDialog() {

}
//===============================================
GQtDialog* GQtDialog::Create(const QString& _key) {
    if(_key == "default") return new GQtDialog;
    if(_key == "qt/find/dialog") return new GQtFindDialog;
    return new GQtDialog;
}
//===============================================

