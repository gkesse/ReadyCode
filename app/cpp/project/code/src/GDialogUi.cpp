//===============================================
#include "GDialogUi.h"
// login
#include "GUserConnect.h"
#include "GUserCreate.h"
// sqlite
#include "GTableShow.h"
#include "GSchemaShow.h"
#include "GTableDelete.h"
//===============================================
GDialogUi::GDialogUi(QWidget* parent) :
QDialog(parent) {
    setWindowTitle("ReadyApp");
    resize(350, 10);
}
//===============================================
GDialogUi::~GDialogUi() {

}
//===============================================
GDialogUi* GDialogUi::Create(const QString& key, QWidget* parent) {
    if(key == "default") {return new GDialogUi(parent);}
    // login
    if(key == "login/user/connect") {return new GUserConnect(parent);}
    if(key == "login/user/create") {return new GUserCreate(parent);}
    // sqlite
    if(key == "sqlite/table/show") {return new GTableShow(parent);}
    if(key == "sqlite/schema/show") {return new GSchemaShow(parent);}
    if(key == "sqlite/table/delete") {return new GTableDelete(parent);}
    // default
    return new GDialogUi(parent);
}
//===============================================
QMap<QString, QString> GDialogUi::getData() {
    return m_dataMap;
}
//===============================================
void GDialogUi::onEvent() {}
void GDialogUi::onEvent(const QString& text) {}
//===============================================
