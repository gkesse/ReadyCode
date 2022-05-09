//===============================================
#include "GQtStackWidget.h"
//===============================================
GQtStackWidget::GQtStackWidget(QWidget* _parent) :
GQtWidget(_parent) {
    m_widgetMap = new QStackedWidget;
}
//===============================================
GQtStackWidget::~GQtStackWidget() {

}
//===============================================
void GQtStackWidget::addWidget(const QString& _key, QWidget* _widget) {
    int lWidgetId = m_widgetMap->addWidget(_widget);
    m_widgetId[_key] = lWidgetId;
}
//===============================================
bool GQtStackWidget::setWidget(const QString& _key) {
    int lWidgetId = m_widgetId.value(_key, -1);
    if(lWidgetId == -1) return false;
    m_widgetMap->setCurrentIndex(lWidgetId);
    return true;
}
//===============================================
