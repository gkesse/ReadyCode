//===============================================
#include "GQtMainWindow.h"
#include "GQtSpreadWindow.h"
//===============================================
GQtMainWindow::GQtMainWindow(QWidget* _parent) :
QMainWindow(_parent) {

}
//===============================================
GQtMainWindow::~GQtMainWindow() {

}
//===============================================
GQtMainWindow* GQtMainWindow::Create(const QString& _key, QWidget* _parent) {
    if(_key == "default") return new GQtMainWindow(_parent);
    if(_key == "page/spreadsheet") return new GQtSpreadWindow(_parent);
    return new GQtMainWindow(_parent);
}
//===============================================

