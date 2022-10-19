//===============================================
#include "GTableWidgetFr.h"
#include "ui_GTableWidgetFr.h"
#include "GTableWidget.h"
#include "GLog.h"
#include "GPath.h"
//===============================================
GTableWidgetFr::GTableWidgetFr(QWidget* _parent)
: QFrame(_parent)
, ui(new Ui::GTableWidgetFr){
    ui->setupUi(this);
    setWindowIcon(QIcon(GPATH("img", "readydev.png").c_str()));
}
//===============================================
GTableWidgetFr::~GTableWidgetFr() {

}
//===============================================
GTableWidget* GTableWidgetFr::getTableWidget() {
    return ui->tableWidget;
}
//===============================================
void GTableWidgetFr::on_btnNext_clicked() {
    GLOGT(eGFUN, "");

}
//===============================================
void GTableWidgetFr::on_tableWidget_itemClicked(QTableWidgetItem *item) {
    GLOGT(eGFUN, "");

}
//===============================================
void GTableWidgetFr::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item) {
    GLOGT(eGFUN, "");

}
//===============================================
