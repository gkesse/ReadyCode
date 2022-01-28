//===============================================
#include "GQtScrollArea.h"
//===============================================
GQtScrollArea::GQtScrollArea(QWidget* _parent) :
QScrollArea(_parent) {

}
//===============================================
GQtScrollArea::~GQtScrollArea() {

}
//===============================================
QSize GQtScrollArea::sizeHint() const {
    int lWidth = widget()->sizeHint().width();
    int lHeight = widget()->sizeHint().height();
    return QSize(lWidth, lHeight);
}
//===============================================
QSize GQtScrollArea::minimumSizeHint() const {
    int lHeight = widget()->sizeHint().height();
    return QSize(0, lHeight + 10);
}
//===============================================
