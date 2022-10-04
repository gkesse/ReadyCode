//===============================================
#include "GTableWidgetUi.h"
#include "ui_GTableWidgetUi.h"
#include "GLog.h"
//===============================================
GTableWidgetUi::GTableWidgetUi(QWidget* _parent)
: QDialog(_parent)
, ui(new Ui::GTableWidgetUi){
    ui->setupUi(this);
    initTableWidget();
}
//===============================================
GTableWidgetUi::~GTableWidgetUi() {

}
//===============================================
void GTableWidgetUi::initTableWidget() {
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setStretchLastSection(false);
    ui->tableWidget->resizeColumnsToContents();
}
//===============================================
void GTableWidgetUi::setSize(int _rows, int _cols) {
    ui->tableWidget->setRowCount(_rows);
    ui->tableWidget->setColumnCount(_cols);
}
//===============================================
void GTableWidgetUi::setHeader(int _col, const GString& _data) {
    ui->tableWidget->horizontalHeader()->show();
    QTableWidgetItem* lItem = new QTableWidgetItem(_data.c_str());
    ui->tableWidget->setHorizontalHeaderItem(_col, lItem);
}
//===============================================
void GTableWidgetUi::setData(int _row, int _col, const GString& _data) {
    QTableWidgetItem* lItem = new QTableWidgetItem(_data.c_str());
    ui->tableWidget->setItem(_row, _col, lItem);
}
//===============================================
void GTableWidgetUi::on_btnSelect_clicked() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GTableWidgetUi::on_btnNext_clicked() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
