//===============================================
#include "GQtUi.h"
#include "GQtUserCreate.h"
#include "GQtUserShow.h"
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
    return new GQtUi;
}
//===============================================
void GQtUi::slotClick() {}
//===============================================
