//===============================================
#include "GQueryUi.h"
#include "ui_GQueryUi.h"
#include "GLog.h"
#include "GQuery.h"
//===============================================
GQueryUi::GQueryUi(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GQueryUi){
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}
//===============================================
GQueryUi::~GQueryUi() {

}
//===============================================
void GQueryUi::readData() {
    m_query.reset(new GQuery);
    // query
    m_query->setEmission(ui->txtEmissionXml->toPlainText());
    m_query->setReception(ui->txtReceptionXml->toPlainText());
}
//===============================================
void GQueryUi::writeData() {
    // query
    ui->txtEmissionXml->setText(m_query->getEmission().c_str());
    ui->txtReceptionXml->setText(m_query->getReception().c_str());
}
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
