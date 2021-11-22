//===============================================
#include "GQtSpreadWindow.h"
#include "GQt.h"
#include "GLog.h"
//===============================================
GQtSpreadWindow::GQtSpreadWindow(QWidget* _parent) :
GQtMainWindow(_parent) {
    sGQt lParams; GQt lQt;
    lParams.app_name = "ReadyApp | Feuille de calculs";

    createActions();

    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);
}
//===============================================
GQtSpreadWindow::~GQtSpreadWindow() {

}
//===============================================
void GQtSpreadWindow::createActions() {
    GLOG->log(GMSG); GQt lQt;
}
//===============================================
