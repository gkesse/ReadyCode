//===============================================
#include "GClient.h"
#include "ui_GClient.h"
#include "GLogUi.h"
//===============================================
GClient::GClient(QWidget* _parent)
: GMainWindow(_parent)
, ui(new Ui::GClient) {
    ui->setupUi(this);
}
//===============================================
GClient::~GClient() {
    delete ui;
}
//===============================================
void GClient::on_actionCalculator_triggered(bool _checked) {
    m_logs.addError("ui_actionCalculator_triggered");
    //m_logs.addData("ui_actionCalculator_triggered");
    m_logs.addLog("ui_actionCalculator_triggered");
    m_logs.showLogsX(this);
}
//===============================================
