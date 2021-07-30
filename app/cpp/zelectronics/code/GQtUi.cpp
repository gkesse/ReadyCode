//===============================================
#include "GQtUi.h"
#include "GQtCircuitRC.h"
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
	if(key == "circuit/rc") {return new GQtCircuitRC;}
	return new GQtUi;
}
//===============================================
void GQtUi::resize() {
	QWidget::resize(400, 100);
}
//===============================================
