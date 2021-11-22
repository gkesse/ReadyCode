//===============================================
#include "GQtDialog.h"
#include "GQtFindDialog.h"
#include "GQtCellLocation.h"
#include "GQtSortDialog.h"
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
    if(_key == "page/finddialog") return new GQtFindDialog(_parent);
    if(_key == "page/celllocation") return new GQtCellLocation(_parent);
    if(_key == "page/sortdialog") return new GQtSortDialog(_parent);
    return new GQtDialog(_parent);
}
//===============================================

