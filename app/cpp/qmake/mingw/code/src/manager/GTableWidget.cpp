//===============================================
#include "GTableWidget.h"
//===============================================
GTableWidget::GTableWidget()
: GObject() {
    m_tableWidget = 0;
    m_rows = 0;
    m_cols = 0;
    m_index = 0;
    m_indexRow = 0;
    m_indexCol = 0;
}
//===============================================
GTableWidget::GTableWidget(int _rows, int _cols, QTableWidget* _tableWidget)
: GObject() {
    _tableWidget->clear();
    m_tableWidget = _tableWidget;
    m_rows = _rows;
    m_cols = _cols;
    m_index = 0;
    m_indexRow = 0;
    m_indexCol = 0;
    setSize();
}
//===============================================
GTableWidget::~GTableWidget() {

}
//===============================================
void GTableWidget::setSize() {
    if(m_rows == 0) return;
    if(m_cols == 0) return;
    m_tableWidget->setRowCount(m_rows);
    m_tableWidget->setColumnCount(m_cols);
}
//===============================================
void GTableWidget::addData(const QString& _data) {
    int lSize = m_rows * m_cols;
    if(m_index >= lSize) return;
    int lRow = m_index / m_cols;
    int lCol = m_index % m_cols;
    QTableWidgetItem* lItem = new QTableWidgetItem(_data);
    m_tableWidget->setItem(lRow, lCol, lItem);
    m_index++;
}
//===============================================
void GTableWidget::addData(int _data, const QVariant& _key) {
    addData(QString("%1").arg(_data), _key);
}
//===============================================
void GTableWidget::addData(const QString& _data, const QVariant& _key) {
    int lSize = m_rows * m_cols;
    if(m_index >= lSize) return;
    int lRow = m_index / m_cols;
    int lCol = m_index % m_cols;
    QTableWidgetItem* lItem = new QTableWidgetItem(_data);
    lItem->setData(Qt::UserRole, _key);
    m_tableWidget->setItem(lRow, lCol, lItem);
    m_index++;
}
//===============================================
void GTableWidget::addRowHeader(const QString& _data) {
    if(m_indexRow >= m_rows) return;
    QTableWidgetItem* lItem = new QTableWidgetItem(_data);
    m_tableWidget->setVerticalHeaderItem(m_indexRow, lItem);
    m_indexRow++;
}
//===============================================
void GTableWidget::addColHeader(const QString& _data) {
    if(m_indexCol >= m_cols) return;
    QTableWidgetItem* lItem = new QTableWidgetItem(_data);
    m_tableWidget->setHorizontalHeaderItem(m_indexCol, lItem);
    m_indexCol++;
}
//===============================================
