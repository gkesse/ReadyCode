//===============================================
#include "GFormLayout.h"
//===============================================
GFormLayout::GFormLayout(QWidget* _parent)
: QFrame(_parent) {
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_widget = new QWidget;
    m_formLayout = new QFormLayout(m_widget);
    m_formLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_widget);
    setLayout(m_mainLayout);
}
//===============================================
GFormLayout::~GFormLayout() {

}
//===============================================
void GFormLayout::addRow(const GString& _key, const GString& _label, const GString& _type) {
    QWidget* lWidget = 0;
    if(_type == "lineedit") {
        lWidget = new QLineEdit;
    }
    else return;
    m_formLayout->addRow(_label.c_str(), lWidget);
    m_widgetMap[_key] = lWidget;
}
//===============================================
GString GFormLayout::getData(const GString& _key, const GString& _type) const {
    GString lData;
    QWidget* lWidget = m_widgetMap.value(_key, 0);
    if(lWidget != 0) {
        if(_type == "lineedit") {
            QLineEdit* lObj = qobject_cast<QLineEdit*>(lWidget);
            lData = lObj->text();
        }
    }
    return lData;
}
//===============================================
void GFormLayout::clear() {
    m_widget->setParent(0);
    delete m_widget;
    m_widget = new QWidget;
    m_formLayout = new QFormLayout(m_widget);
    m_formLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_widget);
}
//===============================================
