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
void GQtUi::onEvent() {}
void GQtUi::onEvent(const QString& text) {}
void GQtUi::onEvent(const QPoint& pos) {}
void GQtUi::onEvent(int row, int col) {}
//===============================================
