//===============================================
#include "GClient.h"
#include "ui_GClient.h"
//===============================================
GClient::GClient(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::GClient) {
    ui->setupUi(this);
}
//===============================================
GClient::~GClient() {
    delete ui;
}
//===============================================
