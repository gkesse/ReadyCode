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
void GFormLayout::addRow(const GString& _label, QWidget* _field) {
    m_formLayout->addRow(_label.c_str(), _field);
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
