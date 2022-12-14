//===============================================
#include "GWindowUi.h"
#include "ui_GWindowUi.h"
#include "GLog.h"
#include "GPath.h"
#include "GFile.h"
#include "GBase64.h"
#include "GOption.h"
#include "GConnection.h"
#include "GModule.h"
#include "GQueryUi.h"
#include "GConfigUi.h"
//===============================================
GWindowUi::GWindowUi(QWidget* _parent)
: QMainWindow(_parent)
, ui(new Ui::GWindowUi){
    ui->setupUi(this);
    setWindowIcon(QIcon(GPATH("img", "readydev.png").c_str()));
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GWindowUi::~GWindowUi() {

}
//===============================================
// managers
//===============================================
void GWindowUi::on_actionConfig_triggered() {
    GLOGT(eGFUN, "");
    GConfigUi* lWindow = new GConfigUi;
    QMdiSubWindow* lSubWindow = ui->mdiArea->addSubWindow(lWindow);
    QPoint lCenter = ui->mdiArea->viewport()->rect().center();
    QRect lGeometry = lSubWindow->geometry();
    lGeometry.moveCenter(lCenter);
    lSubWindow->setGeometry(lGeometry);
    lSubWindow->show();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GWindowUi::on_actionQuery_triggered() {
    GLOGT(eGFUN, "");
    GQueryUi* lWindow = new GQueryUi;
    QMdiSubWindow* lSubWindow = ui->mdiArea->addSubWindow(lWindow);
    QPoint lCenter = ui->mdiArea->viewport()->rect().center();
    QRect lGeometry = lSubWindow->geometry();
    lGeometry.moveCenter(lCenter);
    lSubWindow->setGeometry(lGeometry);
    lSubWindow->show();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
