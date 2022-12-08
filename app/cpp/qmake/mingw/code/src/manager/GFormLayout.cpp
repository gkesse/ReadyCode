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
    if(_key.isEmpty()) return;
    if(_label.isEmpty()) return;
    QWidget* lWidget = 0;
    if(_type == "lineedit") {
        lWidget = new QLineEdit;
    }
    else {
        lWidget = new QLineEdit;
    }
    m_formLayout->addRow(_label.c_str(), lWidget);
    m_widgetMap[_key] = lWidget;
}
//===============================================
void GFormLayout::setData(const GString& _key, const GString& _value, const GString& _type) {
    QWidget* lWidget = m_widgetMap.value(_key, 0);
    if(lWidget != 0) {
        if(_type == "lineedit") {
            QLineEdit* lObj = qobject_cast<QLineEdit*>(lWidget);
            lObj->setText(_value.c_str());
        }
        else {
            QLineEdit* lObj = qobject_cast<QLineEdit*>(lWidget);
            lObj->setText(_value.c_str());
        }
    }
}
//===============================================
void GFormLayout::setId(const GString& _key, const GString& _id) {
    m_idMap[_key] = _id;
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
        else {
            QLineEdit* lObj = qobject_cast<QLineEdit*>(lWidget);
            lData = lObj->text();
        }
    }
    return lData;
}
//===============================================
GString GFormLayout::getId(const GString& _key) const {
    return m_idMap.value(_key, "");
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
