//===============================================
#include "GQtWidget.h"
#include "GQtPicto.h"
//===============================================
GQtWidget::GQtWidget(QWidget* _parent) :
QFrame(_parent) {

}
//===============================================
GQtWidget::~GQtWidget() {

}
//===============================================
QPushButton* GQtWidget::createButtonIcon(const QString& _text, QPushButton** _icon) {
    QPushButton* lButton = new QPushButton;
    lButton->setObjectName("button_icon");
    lButton->setText(_text);

    QPushButton* lIcon = new QPushButton(lButton);
    lIcon->setObjectName("button_icon_icon");
    lIcon->move(0, 0);
    lIcon->setIcon(GQTPICTO("user", "white"));

    int w1 = lButton->sizeHint().width();
    int h1 = lButton->sizeHint().height();
    int w2 = lIcon->sizeHint().width();
    int h2 = lIcon->sizeHint().height();
    int lX = (w1 - w2 -10);
    int lY = (h1 - h2) / 2;

    lIcon->move(lX, lY);

    (*_icon) = lIcon;
    return lButton;
}
//===============================================
QLineEdit* GQtWidget::createLineEditIcon(QPushButton** _icon) {
    QLineEdit* lLineEdit = new QLineEdit;
    lLineEdit->setObjectName("lineedit_icon");

    QPushButton* lIcon = new QPushButton(lLineEdit);
    lIcon->setObjectName("lineedit_icon_icon");
    lIcon->move(0, 0);
    lIcon->setIcon(GQTPICTO("user", "white"));

    int h1 = lLineEdit->sizeHint().height();
    int h2 = lIcon->sizeHint().height();
    int lY = (h1 - h2) / 2;

    lIcon->move(10, lY);

    (*_icon) = lIcon;
    return lLineEdit;
}
//===============================================
