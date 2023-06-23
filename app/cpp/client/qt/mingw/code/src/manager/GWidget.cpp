//===============================================
#include "GWidget.h"
//===============================================
GWidget::GWidget(QWidget* _parent)
: QWidget(_parent) {
    m_clientUi = 0;
}
//===============================================
GWidget::~GWidget() {

}
//===============================================
void GWidget::setClientUi(GClientUi* _clientUi) {
    m_clientUi = _clientUi;
}
//===============================================
