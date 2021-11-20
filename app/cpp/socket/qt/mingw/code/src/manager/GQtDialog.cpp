//===============================================
#include "GQtDialog.h"
#include "GQtFindDialog.h"
#include "GQtCellLocation.h"
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
    if(_key == "qt/find/dialog") return new GQtFindDialog(_parent);
    if(_key == "qt/cell/location") return new GQtCellLocation(_parent);
    return new GQtDialog(_parent);
}
//===============================================

