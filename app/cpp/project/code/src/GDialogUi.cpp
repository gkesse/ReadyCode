//===============================================
#include "GDialogUi.h"
// sqlite
#include "GSchemaShow.h"
//===============================================
GDialogUi::GDialogUi(QWidget* parent) :
QDialog(parent) {
	setWindowTitle("ReadyApp");
	resize(400, 100);
}
//===============================================
GDialogUi::~GDialogUi() {

}
//===============================================
GDialogUi* GDialogUi::Create(const QString& key, QWidget* parent) {
    if(key == "default") {return new GDialogUi(parent);}
    // sqlite
    if(key == "sqlite/schema/show") {return new GSchemaShow(parent);}
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
