//===============================================
#include "GQtUi.h"
#include "GQtUserCreate.h"
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
    return new GQtUi;
}
//===============================================
void GQtUi::slotClick() {}
//===============================================
