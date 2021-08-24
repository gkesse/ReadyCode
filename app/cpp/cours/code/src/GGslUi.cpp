//===============================================
#include "GGslUi.h"
#include "GDifferentiation.h"
#include "GIntegration.h"
//===============================================
GGslUi::GGslUi(QWidget* parent) :
QFrame(parent) {

}
//===============================================
GGslUi::~GGslUi() {

}
//===============================================
GGslUi* GGslUi::Create(const QString& key) {
    if(key == "default") {return new GGslUi;}
    if(key == "differentiation") {return new GDifferentiation;}
    if(key == "integration") {return new GIntegration;}
    return new GGslUi;
}
//===============================================
void GGslUi::resize() {QFrame::resize(400, 100);}
//===============================================
void GGslUi::onEvent() {}
void GGslUi::onEvent(const QString& text) {}
void GGslUi::onEvent(const QPoint& pos) {}
void GGslUi::onEvent(int row, int col) {}
//===============================================
