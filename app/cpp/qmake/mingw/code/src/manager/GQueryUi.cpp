//===============================================
#include "GQueryUi.h"
#include "ui_GQueryUi.h"
#include "GQuery.h"
#include "GQueryType.h"
//===============================================
GQueryUi::GQueryUi(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GQueryUi){
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    m_typeId = 0;

    onLoadSearchConfig();
}
//===============================================
GQueryUi::~GQueryUi() {

}
//===============================================
void GQueryUi::readData() {
    m_query.reset(new GQuery);
    m_queryType.reset(new GQueryType);
    // type
    m_queryType->setId(m_typeId);
    m_queryType->setName(ui->edtNameCreateType->text());
    // emission
    m_query->setEmission(ui->txtEmission->toPlainText());
    // reception
    m_query->setReception(ui->txtReception->toPlainText());
}
//===============================================
void GQueryUi::writeData() {
    // type
    m_typeId = m_queryType->getId();
    ui->edtNameCreateType->setText(m_queryType->getName().c_str());
    // emission
    ui->txtEmission->setText(m_query->getEmission().c_str());
    // reception
    ui->txtReception->setText(m_query->getReception().c_str());
}
//===============================================
// xml
//===============================================
void GQueryUi::on_btnSendEmissionXml_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_query->sendQuery();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GQueryUi::on_btnNewEmissionXml_clicked() {
    GLOGT(eGFUN, "");
    m_query.reset(new GQuery);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// type
//===============================================
void GQueryUi::onLoadDefaultComboBox() {
    GLOGT(eGFUN, "");
    readData();
    m_query->saveTypeQuery();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GQueryUi::on_btnSaveCreateType_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_queryType->saveQueryType();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GQueryUi::on_btnSearchCreateType_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_queryType->setSearch(m_searchConfig);
    m_queryType->searchQueryType();
    m_queryType->showList();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GQueryUi::on_btnDeleteCreateType_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_queryType->deleteQueryType();
    m_queryType.reset(new GQueryType);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GQueryUi::on_btnNewCreateType_clicked() {
    GLOGT(eGFUN, "");
    m_queryType.reset(new GQueryType);
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// emission
//===============================================
void GQueryUi::on_btnSendEmission_clicked() {
    GLOGT(eGFUN, "");
    readData();
    m_query->sendQuery();
    writeData();
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
void GQueryUi::on_btnClearEmission_clicked() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// reception
//===============================================
void GQueryUi::on_btnCopyReception_clicked() {
    GLOGT(eGFUN, "");
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
// search
//===============================================
void GQueryUi::onLoadSearchConfig() {
    GLOGT(eGFUN, "");
    m_searchConfig.reset(new GSearch);
    m_searchConfig->setDataSize(10);
    GERROR_SHOWG(eGERR);
    GLOG_SHOWG(eGLOG);
}
//===============================================
