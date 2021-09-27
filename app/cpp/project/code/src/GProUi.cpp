//===============================================
#include "GProUi.h"
// login
#include "GLoginPage.h"
// sqlite
#include "GSQLitePage.h"
//===============================================
GProUi::GProUi(QWidget* parent) :
QFrame(parent) {

}
//===============================================
GProUi::~GProUi() {

}
//===============================================
GProUi* GProUi::Create(const QString& key, QWidget* parent) {
    if(key == "default") {return new GProUi(parent);}
    // login
    if(key == "login/page") {return new GLoginPage(parent);}
    // sqlite
    if(key == "sqlite/page") {return new GSQLitePage(parent);}
    // default
    return new GProUi(parent);
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
void GProUi::setCenter(QWidget* parent) {
    move(QPoint(parent->x(), parent->y()) + parent->rect().center() - rect().center());
}
//===============================================
QMap<QString, QString> GProUi::getData() {
    return m_dataMap;
}
//===============================================
void GProUi::onEvent() {}
void GProUi::onEvent(const QString& text) {}
//===============================================
