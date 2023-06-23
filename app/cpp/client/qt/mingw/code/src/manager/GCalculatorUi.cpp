//===============================================
#include "GCalculatorUi.h"
#include "ui_GCalculatorUi.h"
#include "GCalculator.h"
//===============================================
GCalculatorUi::GCalculatorUi(QWidget* _parent)
: GWidget(_parent)
, ui(new Ui::GCalculatorUi) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GCalculatorUi::~GCalculatorUi() {
    delete ui;
}
//===============================================
void GCalculatorUi::on_edtExpression_returnPressed() {
    GCalculator lCalculator;
    lCalculator.setFacade(m_clientUi->getFacade());
    lCalculator.setExpression(ui->edtExpression->text());
    lCalculator.runCalculator();
    m_logs.addLogs(lCalculator.getLogs());
    m_logs.showLogsX(this);
}
//===============================================
