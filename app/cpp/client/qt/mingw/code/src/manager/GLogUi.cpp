//===============================================
#include "GLogUi.h"
#include "ui_GLogUi.h"
//===============================================
GLogUi* GLogUi::m_instance = 0;
//===============================================
GLogUi::GLogUi(QWidget *parent)
: GDialog(parent)
, ui(new Ui::GLogUi) {
    ui->setupUi(this);
}
//===============================================
GLogUi::~GLogUi() {
    delete ui;
}
//===============================================
GLogUi* GLogUi::Instance() {
    if(m_instance == 0) {
        m_instance = new GLogUi;
    }
    return m_instance;
}
//===============================================
