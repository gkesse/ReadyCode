//===============================================
#include "GTableWidget.h"
//===============================================
GTableWidget::GTableWidget(QObject* _parent) : GObject(_parent) {
    m_tableWidget = 0;
    m_rows = 0;
    m_cols = 0;
    m_index = 0;
}
//===============================================
GTableWidget::GTableWidget(int _rows, int _cols, QTableWidget* _tableWidget, QObject* _parent) : GObject(_parent) {
    m_tableWidget = _tableWidget;
    m_rows = _rows;
    m_cols = _cols;
    m_index = 0;
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
