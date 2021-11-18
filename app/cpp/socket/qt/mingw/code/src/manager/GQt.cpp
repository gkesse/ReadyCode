//===============================================
#include "GQt.h"
//===============================================
GQt::GQt(QObject* _parent) : QObject(_parent) {
	m_QWidget = 0;
	m_QBoxLayout = 0;
	m_QPushButton = 0;
	m_QTextEdit = 0;
	m_QSpinBox = 0;
	m_QSlider = 0;
	m_QVBoxLayout = 0;
	m_QHBoxLayout = 0;
}
//===============================================
GQt::~GQt() {

}
//===============================================
GQt& GQt::createQPushButton(const QString& _name) {
	m_QPushButton = new QPushButton;
	m_QPushButton->setText(_name);
	m_QWidget = m_QPushButton;
    return *this;
}
//===============================================
GQt& GQt::createQPushButton(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap) {
	m_QPushButton = new QPushButton;
	m_QPushButton->setText(_name);
    _QWidgetMap[m_QPushButton] = _key;
	m_QWidget = m_QPushButton;
    return *this;
}
//===============================================
GQt& GQt::createQTextEdit() {
    m_QTextEdit = new QTextEdit;
    m_QTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "border:none;"
            "background-color:black;"
            "color:white;"
            "font-family:courier new;"
            "font-size:14px;"
            "}"));
    m_QTextEdit->setLineWrapMode(QTextEdit::NoWrap);
	m_QWidget = m_QTextEdit;
    return *this;
}
//===============================================
GQt& GQt::createQSpinBox() {
	m_QSpinBox = new QSpinBox;
	m_QWidget = m_QSpinBox;
	return *this;
}
//===============================================
GQt& GQt::createQSlider() {
	m_QSlider = new QSlider;
	m_QWidget = m_QSlider;
	return *this;
}
//===============================================
GQt& GQt::createQVBoxLayout() {
	m_QVBoxLayout = new QVBoxLayout;
	m_QBoxLayout = m_QVBoxLayout;
	return *this;
}
//===============================================
GQt& GQt::createQHBoxLayout() {
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
GQt& GQt::setWidget(QWidget* _widget) {
	m_QWidget = _widget;
	return *this;
}
//===============================================
GQt& GQt::setWindowTitle(const QString _title) {
	m_QWidget->setWindowIconText(_title);
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
GQt& GQt::getDataQTextEdit(std::string& _data) {
	_data = m_QTextEdit->toPlainText().toStdString();
	return *this;
}
//===============================================
GQt& GQt::getKey(int _argc, char** _argv, int _index, QString& _key) {
    _key = "default";
    if(_argc > _index) {
    	_key = _argv[_index];
    }
    return *this;
}
//===============================================
bool GQt::isEmptyQTextEdit() {
	return m_QTextEdit->toPlainText().isEmpty();
}
//===============================================
