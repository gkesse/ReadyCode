//===============================================
#include "GQt.h"
//===============================================
GQt::GQt(QObject* _parent) : QObject(_parent) {
	m_QWidget = 0;
	m_QBoxLayout = 0;
	m_QPushButton = 0;
	m_QTextEdit = 0;
	m_QVBoxLayout = 0;
	m_QHBoxLayout = 0;
}
//===============================================
GQt::~GQt() {

}
//===============================================
GQt& GQt::createButton(const QString& _name, const QString& _key) {
	m_QPushButton = new QPushButton;
	m_QPushButton->setText(_name);
    m_QWidgetMap[m_QPushButton] = _key;
	m_QWidget = m_QPushButton;
    return *this;
}
//===============================================
GQt& GQt::createTextEdit() {
    m_QTextEdit = new QTextEdit;
    m_QTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "border:none;"
            "background-color:black;"
            "color:white;"
            "font-size:14px;"
            "}"));
    m_QTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_QTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_QWidget = m_QTextEdit;
    return *this;
}
//===============================================
GQt& GQt::createVBoxLayout() {
	m_QVBoxLayout = new QVBoxLayout;
	m_QBoxLayout = m_QVBoxLayout;
	return *this;
}
//===============================================
GQt& GQt::createHBoxLayout() {
	m_QHBoxLayout = new QHBoxLayout;
	m_QBoxLayout = m_QHBoxLayout;
	return *this;
}
//===============================================
GQt& GQt::addWidget(const GQt& _widget) {
	m_QBoxLayout->addWidget(_widget.m_QWidget);
	return *this;
}
//===============================================
GQt& GQt::addLayout(const GQt& _layout) {
	m_QBoxLayout->addLayout(_layout.m_QBoxLayout);
	return *this;
}
//===============================================
GQt& GQt::setLayout(QWidget* _widget) {
	_widget->setLayout(m_QBoxLayout);
	return *this;
}
//===============================================
GQt& GQt::setAlignment(Qt::Alignment _alignment) {
	m_QBoxLayout->setAlignment(_alignment);
	return *this;
}
//===============================================
GQt& GQt::connectObject(const char* _signal, const QObject* _member, const char* _slot) {
	connect(m_QWidget, _signal, _member, _slot);
	return *this;
}
//===============================================
