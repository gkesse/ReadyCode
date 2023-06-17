//===============================================
#include "GClient.h"
#include "ui_GClient.h"
#include "GCalculatorUi.h"
//===============================================
GClient::GClient(QWidget* _parent)
: GMainWindow(_parent)
, ui(new Ui::GClient) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GClient::~GClient() {
    delete ui;
}
//===============================================
void GClient::on_actionCalculator_triggered(bool _checked) {
    GCalculatorUi* lCalculatorUi = new GCalculatorUi;
    lCalculatorUi->show();
}
//===============================================
void GClient::closeEvent(QCloseEvent* _event) {
    qApp->closeAllWindows();
    _event->accept();
}
//===============================================
