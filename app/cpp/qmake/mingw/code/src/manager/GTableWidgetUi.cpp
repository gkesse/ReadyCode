//===============================================
#include "GTableWidgetUi.h"
#include "ui_GTableWidgetUi.h"
#include "GLog.h"
//===============================================
GTableWidgetUi::GTableWidgetUi(QWidget* _parent)
: QDialog(_parent)
, ui(new Ui::GTableWidgetUi){
    ui->setupUi(this);
}
//===============================================
GTableWidgetUi::~GTableWidgetUi() {

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
