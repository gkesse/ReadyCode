//===============================================
#include "GQtDialog.h"
//===============================================
GQtDialog::GQtDialog(QWidget* _parent) :
QDialog(_parent) {

}
//===============================================
GQtDialog::~GQtDialog() {

}
//===============================================
GQtDialog* GQtDialog::Create(const QString& _key, QWidget* _parent) {
    if(_key == "default") return new GQtDialog(_parent);
    return new GQtDialog(_parent);
}
//===============================================

