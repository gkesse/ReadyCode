//===============================================
#include "GTreeWidgetUi.h"
#include "GLog.h"
//===============================================
GTreeWidgetUi::GTreeWidgetUi(QWidget* _parent)
: QTreeWidget(_parent) {
    m_header = 0;
    m_root = 0;
    m_child = 0;
    m_node = 0;
    //
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    resizeColumnToContents(0);
    header()->show();
    header()->setStretchLastSection(true);
    header()->setMinimumSectionSize(0);
    setFocusPolicy(Qt::NoFocus);
}
//===============================================
GTreeWidgetUi::~GTreeWidgetUi() {

}
//===============================================
void GTreeWidgetUi::addHeader() {
    m_header = new QTreeWidgetItem();
    setHeaderItem(m_header);
    m_node = m_header;
}
//===============================================
void GTreeWidgetUi::addRoot() {
    m_root = new QTreeWidgetItem(this);
    m_node = m_root;
}
//===============================================
void GTreeWidgetUi::initRoot() {
    m_root = m_child;
}
//===============================================
void GTreeWidgetUi::addChild() {
    m_child = new QTreeWidgetItem();
    m_root->addChild(m_child);
    m_node = m_child;
}
//===============================================
void GTreeWidgetUi::setData(int _col, const GString& _data) {
    m_node->setText(_col, _data.c_str());
}
//===============================================
