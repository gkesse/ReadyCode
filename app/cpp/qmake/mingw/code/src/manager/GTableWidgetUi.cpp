//===============================================
#include "GTableWidgetUi.h"
#include "ui_GTableWidgetUi.h"
#include "GLog.h"
#include "GPath.h"
//===============================================
GTableWidgetUi::GTableWidgetUi(QWidget* _parent)
: QDialog(_parent)
, ui(new Ui::GTableWidgetUi){
    ui->setupUi(this);
    initTableWidget();
    setWindowIcon(QIcon(GPATH("img", "readydev.png").c_str()));
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
    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(0);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    m_index = 0;
    m_search = 0;
}
//===============================================
void GTableWidgetUi::setSearch(GSearch* _search) {
    m_search = _search;
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
int GTableWidgetUi::getIndex() const {
    return m_index;
}
//===============================================
void GTableWidgetUi::on_btnSelect_clicked() {
    accept();
}
//===============================================
void GTableWidgetUi::on_btnNext_clicked() {
    if(!m_search) {GERROR_ADD(eGERR, "L'objet recherché n'a pas été initialisé."); return;}
    m_search->onNextData();
}
//===============================================
void GTableWidgetUi::on_tableWidget_cellClicked(int row, int column) {
    m_index = row;
}
//===============================================
void GTableWidgetUi::on_tableWidget_cellDoubleClicked(int row, int column) {
    accept();
}
//===============================================
