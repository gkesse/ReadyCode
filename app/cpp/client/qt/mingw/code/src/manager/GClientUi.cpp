//===============================================
#include "GClientUi.h"
#include "ui_GClientUi.h"
#include "GCalculatorUi.h"
#include "GFormUi.h"
//===============================================
GClientUi::GClientUi(QWidget* _parent)
: GMainWindow(_parent)
, ui(new Ui::GClientUi) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GClientUi::~GClientUi() {
    delete ui;
}
//===============================================
void GClientUi::on_actionFacade_triggered(bool _checked) {
    GFormUi lFacade;
    lFacade.addItem("serveur_c");
    lFacade.addItem("serveur_cpp");
    lFacade.addItem("serveur_python");

    GFormUi lFacadeV;
    lFacadeV.setValue("serveur_python");
    int lFacadeI = lFacade.indexOf(lFacadeV);

    GFormUi lFormUi(this);
    lFormUi.addComboBox("Facade", lFacade.serialize(), lFacadeI);

    if(lFormUi.run() == QDialog::Accepted) {
        lFormUi.loadFromMap(1).getValue().print();
    }
}
//===============================================
void GClientUi::on_actionCalculator_triggered(bool _checked) {
    GCalculatorUi* lWindow = new GCalculatorUi;
    QMdiSubWindow* lSubWindow = ui->mdiArea->addSubWindow(lWindow);
    QPoint lCenter = ui->mdiArea->viewport()->rect().center();
    QRect lGeometry = lSubWindow->geometry();
    lGeometry.moveCenter(lCenter);
    lSubWindow->setGeometry(lGeometry);
    lSubWindow->show();
}
//===============================================
void GClientUi::closeEvent(QCloseEvent* _event) {
    qApp->closeAllWindows();
    _event->accept();
}
//===============================================
