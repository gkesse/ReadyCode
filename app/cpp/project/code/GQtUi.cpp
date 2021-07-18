//===============================================
#include "GQtUi.h"
#include "GQtUserCreate.h"
#include "GQtUserShow.h"
#include "GQtUserConnect.h"
//===============================================
GQtUi::GQtUi(QWidget* parent) : 
QWidget(parent) {

}
//===============================================
GQtUi::~GQtUi() {

}
//===============================================
GQtUi* GQtUi::Create(const QString& key) {
    if(key == "default") {return new GQtUi;}
    if(key == "usercreate") {return new GQtUserCreate;}
    if(key == "usershow") {return new GQtUserShow;}
    if(key == "userconnect") {return new GQtUserConnect;}
    return new GQtUi;
}
//===============================================
void GQtUi::onEvent(const QString& event) {}
void GQtUi::slotEvent() {}
void GQtUi::slotEvent(const QPoint& pos) {}
void GQtUi::slotEvent(int row, int col) {}
//===============================================
