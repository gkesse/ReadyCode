//===============================================
#include "GProUi.h"
// login
#include "GUserConnect.h"
// sqlite
#include "GDatabaseUpdate.h"
//===============================================
GProUi::GProUi(QWidget* parent) :
QFrame(parent) {

}
//===============================================
GProUi::~GProUi() {

}
//===============================================
GProUi* GProUi::Create(const QString& key) {
    if(key == "default") {return new GProUi;}
    // login
    if(key == "login/user/connect") {return new GUserConnect;}
    // sqlite
    if(key == "sqlite/database/update") {return new GDatabaseUpdate;}
    // default
    return new GProUi;
}
//===============================================
void GProUi::setTitle() {
    setWindowTitle("ReadyApp");
}
//===============================================
void GProUi::setSize() {
    resize(400, 100);
}
//===============================================
void GProUi::onEvent() {}
void GProUi::onEvent(const QString& text) {}
//===============================================
