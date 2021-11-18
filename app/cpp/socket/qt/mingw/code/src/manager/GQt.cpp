//===============================================
#include "GQt.h"
//===============================================
GQt::GQt(QObject* _parent) : QObject(_parent) {
	m_eGType = eUnknown;
	m_QWidget = 0;
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
GQt& GQt::createQWidget() {
	m_eGType = eQWidget;
	m_QWidget = new QWidget;
	return *this;
}
//===============================================
GQt& GQt::createQPushButton(const QString& _name) {
	m_eGType = eQPushButton;
	m_QPushButton = new QPushButton;
	m_QPushButton->setText(_name);
    return *this;
}
//===============================================
GQt& GQt::createQPushButton(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap) {
	m_eGType = eQPushButton;
	m_QPushButton = new QPushButton;
	m_QPushButton->setText(_name);
    _QWidgetMap[m_QPushButton] = _key;
    return *this;
}
//===============================================
GQt& GQt::createQTextEdit() {
	m_eGType = eQTextEdit;
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
    return *this;
}
//===============================================
GQt& GQt::createQSpinBox() {
	m_eGType = eQSpinBox;
	m_QSpinBox = new QSpinBox;
	return *this;
}
//===============================================
GQt& GQt::createQSlider() {
	m_eGType = eQSlider;
	m_QSlider = new QSlider;
	return *this;
}
//===============================================
GQt& GQt::createQVBoxLayout() {
	m_eGType = eQVBoxLayout;
	m_QVBoxLayout = new QVBoxLayout;
	return *this;
}
//===============================================
GQt& GQt::createQHBoxLayout() {
	m_eGType = eQHBoxLayout;
	m_QHBoxLayout = new QHBoxLayout;
	return *this;
}
//===============================================
GQt& GQt::addWidget(GQt& _widget) {
	if(m_eGType == eQHBoxLayout) m_QHBoxLayout->addWidget(_widget.getQWidget());
	if(m_eGType == eQVBoxLayout) m_QVBoxLayout->addWidget(_widget.getQWidget());
	return *this;
}
//===============================================
GQt& GQt::addLayout(GQt& _layout) {
	getQBoxLayout()->addLayout(_layout.getQBoxLayout());
	return *this;
}
//===============================================
GQt& GQt::setQWidget(QWidget* _widget) {
	m_eGType = eQWidget;
	m_QWidget = _widget;
	return *this;
}
//===============================================
GQt& GQt::setWindowTitle(const QString& _title) {
	getQWidget()->setWindowIconText(_title);
	return *this;
}
//===============================================
GQt& GQt::setLayout(QWidget* _widget) {
	_widget->setLayout(getQBoxLayout());
	return *this;
}
//===============================================
GQt& GQt::setAlignment(Qt::Alignment _alignment) {
	getQBoxLayout()->setAlignment(_alignment);
	return *this;
}
//===============================================
GQt& GQt::setRangeQSlider(int _min, int _max) {
	m_QSlider->setRange(_min, _max);
	return *this;
}
//===============================================
GQt& GQt::setRangeQSpinBox(int _min, int _max) {
	m_QSpinBox->setRange(_min, _max);
	return *this;
}
//===============================================
GQt& GQt::connectObject(const char* _signal, const QObject* _member, const char* _slot) {
	connect(getQWidget(), _signal, _member, _slot);
	return *this;
}
//===============================================
QWidget* GQt::getQWidget() {
	if(m_eGType == eQWidget) return m_QWidget;
	if(m_eGType == eQPushButton) return m_QPushButton;
	if(m_eGType == eQTextEdit) return m_QTextEdit;
	if(m_eGType == eQSpinBox) return m_QSpinBox;
	if(m_eGType == eQSlider) return m_QSlider;
	return 0;
}
//===============================================
QBoxLayout* GQt::getQBoxLayout() {
	if(m_eGType == eQVBoxLayout) return m_QVBoxLayout;
	if(m_eGType == eQHBoxLayout) return m_QHBoxLayout;
	return 0;
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
