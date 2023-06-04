//===============================================
#include "GTableWidget.h"
//===============================================
GTableWidget::GTableWidget(QWidget* _parent)
: QTableWidget(_parent) {
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setStretchLastSection(false);
    resizeColumnsToContents();
    horizontalHeader()->setMinimumSectionSize(0);
    setFocusPolicy(Qt::NoFocus);

    connect(this, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onItemClicked(QTableWidgetItem*)));
}
//===============================================
GTableWidget::~GTableWidget() {

}
//===============================================
void GTableWidget::setSize(int _rows, int _cols) {
    setRowCount(_rows);
    setColumnCount(_cols);
}
//===============================================
void GTableWidget::setHeader(int _col, const GString& _data) {
    horizontalHeader()->show();
    QTableWidgetItem* lItem = new QTableWidgetItem(_data.c_str());
    setHorizontalHeaderItem(_col, lItem);
}
//===============================================
void GTableWidget::setData(int _row, int _col, const GString& _key, const GString& _data) {
    QTableWidgetItem* lItem = new QTableWidgetItem(_data.c_str());
    lItem->setData(Qt::UserRole, _key.c_str());
    setItem(_row, _col, lItem);
}
//===============================================
void GTableWidget::addRow() {
    insertRow(rowCount());
}
//===============================================
void GTableWidget::addCol(int _col, const GString& _key, const GString& _data) {
    int lRow = rowCount() - 1;
    setData(lRow, _col, _key, _data);
}
//===============================================
void GTableWidget::setKey(const GString& _key) {
    m_key = _key;
}
//===============================================
GString GTableWidget::getKey() const {
    return m_key;
}
//===============================================
void GTableWidget::onItemClicked(QTableWidgetItem* _item) {
    m_key = _item->data(Qt::UserRole).toString();
}
//===============================================
