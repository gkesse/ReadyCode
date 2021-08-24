//===============================================
#include "GQtUi.h"
#include "GAnalogClock.h"
#include "GCalculator.h"
#include "GCalendar.h"
//===============================================
GQtUi::GQtUi(QWidget* parent) :
QFrame(parent) {

}
//===============================================
GQtUi::~GQtUi() {

}
//===============================================
GQtUi* GQtUi::Create(const QString& key) {
    if(key == "default") {return new GQtUi;}
    if(key == "widget/analogclock") {return new GAnalogClock;}
    if(key == "widget/calculator") {return new GCalculator;}
    if(key == "widget/calendar") {return new GCalendar;}
    return new GQtUi;
}
//===============================================
void GQtUi::resize() {QFrame::resize(400, 100);}
//===============================================
void GQtUi::onEvent() {}
void GQtUi::onEvent(const QString& text) {}
void GQtUi::onEvent(const QPoint& pos) {}
void GQtUi::onEvent(int row, int col) {}
//===============================================
