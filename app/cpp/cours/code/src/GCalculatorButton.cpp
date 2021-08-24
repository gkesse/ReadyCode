//===============================================
#include "GCalculatorButton.h"
//===============================================
GCalculatorButton::GCalculatorButton(const QString &text, QWidget* parent) : QToolButton(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}
//===============================================
GCalculatorButton::~GCalculatorButton() {

}
//===============================================
QSize GCalculatorButton::sizeHint() const {
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
//===============================================
