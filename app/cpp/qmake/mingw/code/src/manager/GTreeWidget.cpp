//===============================================
#include "GTreeWidget.h"
#include "GLog.h"
//===============================================
GTreeWidget::GTreeWidget(QWidget* _parent)
: QTreeWidget(_parent) {
    m_header = 0;
    m_root = 0;
    m_child = 0;
    m_node = 0;

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    resizeColumnToContents(0);
    header()->show();
    header()->setStretchLastSection(true);
    header()->setMinimumSectionSize(0);
    setFocusPolicy(Qt::NoFocus);
}
//===============================================
GTreeWidget::~GTreeWidget() {

}
//===============================================
void GTreeWidget::addHeader() {
    m_header = new QTreeWidgetItem();
    setHeaderItem(m_header);
    m_node = m_header;
}
//===============================================
void GTreeWidget::addRoot() {
    m_root = new QTreeWidgetItem(this);
    m_node = m_root;
}
//===============================================
void GTreeWidget::initRoot() {
    m_root = m_child;
}
//===============================================
void GTreeWidget::addChild() {
    m_child = new QTreeWidgetItem();
    m_root->addChild(m_child);
    m_node = m_child;
}
//===============================================
void GTreeWidget::setData(int _col, const GString& _key, const GString& _data) {
    m_node->setData(_col, Qt::UserRole, _key.c_str());
    m_node->setText(_col, _data.c_str());
}
//===============================================
void GTreeWidget::selectItem() {
    m_node->setSelected(true);
}
//===============================================
