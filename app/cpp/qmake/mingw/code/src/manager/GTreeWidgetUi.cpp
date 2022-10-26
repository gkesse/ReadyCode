//===============================================
#include "GTreeWidgetUi.h"
#include "ui_GTreeWidgetUi.h"
#include "GLog.h"
#include "GPath.h"
#include "GSearch.h"
//===============================================
GTreeWidgetUi::GTreeWidgetUi(QWidget* _parent)
: QDialog(_parent)
, ui(new Ui::GTreeWidgetUi){
    ui->setupUi(this);
    setWindowIcon(QIcon(GPATH("img", "readydev.png").c_str()));
    m_search = 0;
}
//===============================================
GTreeWidgetUi::~GTreeWidgetUi() {

}
//===============================================
void GTreeWidgetUi::setSearch(GSearch* _search) {
    m_search = _search;
    ui->btnNext->setEnabled(m_search->hasData());
}
//===============================================
void GTreeWidgetUi::setKey(const GString& _key) {
    m_key = _key;
}
//===============================================
GTreeWidget* GTreeWidgetUi::getTreeWidget() {
    return ui->treeWidget;
}
//===============================================
GString GTreeWidgetUi::getKey() const {
    return m_key;
}
//===============================================
void GTreeWidgetUi::on_btnSelect_clicked() {
    if(!m_key.isEmpty()) {
        accept();
    }
}
//===============================================
void GTreeWidgetUi::on_btnNext_clicked() {
    if(!m_search) {
        GERROR_ADD(eGERR, "L'objet recherché n'a pas été initialisé.");
    }
    else {
        m_search->onNextData();
    }
    ui->btnNext->setEnabled(m_search->hasData());
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GTreeWidgetUi::on_btnAdd_clicked() {
    m_search->onAddData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GTreeWidgetUi::on_btnMoveUp_clicked() {
    m_search->onMoveUpData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GTreeWidgetUi::on_btnMoveDown_clicked() {
    m_search->onMoveDownData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GTreeWidgetUi::on_treeWidget_itemClicked(QTreeWidgetItem* _item, int _column) {
    m_key = _item->data(_column, Qt::UserRole).toString();
}
//===============================================
void GTreeWidgetUi::on_treeWidget_itemDoubleClicked(QTreeWidgetItem* _item, int _column) {
    on_btnSelect_clicked();
}
//===============================================
