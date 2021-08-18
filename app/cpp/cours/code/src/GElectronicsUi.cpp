//===============================================
#include "GElectronicsUi.h"
#include "GCircuitRC.h"
//===============================================
GElectronicsUi::GElectronicsUi(QWidget* parent) : 
QFrame(parent) {

}
//===============================================
GElectronicsUi::~GElectronicsUi() {

}
//===============================================
GElectronicsUi* GElectronicsUi::Create(const QString& key) {
    if(key == "default") {return new GElectronicsUi;}
    if(key == "circuit/rc") {return new GCircuitRC;}
    return new GElectronicsUi;
}
//===============================================
void GElectronicsUi::onEvent() {}
void GElectronicsUi::onEvent(const QString& text) {}
void GElectronicsUi::onEvent(const QPoint& pos) {}
void GElectronicsUi::onEvent(int row, int col) {}
//===============================================
