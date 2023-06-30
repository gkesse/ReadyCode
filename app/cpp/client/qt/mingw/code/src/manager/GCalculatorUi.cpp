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
    ui->layResult->setAlignment(Qt::AlignTop);
    m_layResult = 0;
}
//===============================================
GCalculatorUi::~GCalculatorUi() {
    delete ui;
}
//===============================================
void GCalculatorUi::addCalculator(const GCalculator& _calc, int i, int _size) {
    QLabel* lResultLabel = new QLabel;
    lResultLabel->setText(sformat("(%d/%d) : %s\n= %s"
            , i
            , _size
            , _calc.getExpression().c_str()
            , _calc.getResult().c_str()
            ).c_str());
    m_layResult->addWidget(lResultLabel);
}
//===============================================
void GCalculatorUi::showCalculator() {
    int lSize = m_calcMap.size();
    if(!m_calcMap.size()) return;
    m_widResult.reset(new QWidget);
    m_layResult = new QVBoxLayout(m_widResult.get());
    for(int i = lSize; i >= 1; i--) {
        m_calcMap.loadFromMap(i);
        addCalculator(m_calcMap, i, lSize);
    }
    ui->layResult->addWidget(m_widResult.get());
}
//===============================================
void GCalculatorUi::on_edtExpression_returnPressed() {
    GCalculator lCalc;
    lCalc.setFacade(m_clientUi->getFacade());
    lCalc.setExpression(ui->edtExpression->text());
    lCalc.runCalculator();
    m_logs.addLogs(lCalc.getLogs());

    if(!m_logs.hasErrors()) {
        m_calcMap.addObj(lCalc);
        showCalculator();
    }

    m_logs.showLogsX(this);
}
//===============================================
