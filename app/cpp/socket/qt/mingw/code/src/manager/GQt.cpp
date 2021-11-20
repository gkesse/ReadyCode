//===============================================
#include "GQt.h"
//===============================================
GQt::GQt(QObject* _parent) : QObject(_parent) {
    m_eGType = eUnknown;
    m_QWidget = 0;
    m_QPushButton = 0;
    m_QCheckBox = 0;
    m_QLabel = 0;
    m_QLineEdit = 0;
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
GQt& GQt::createQWidget(QWidget* _parent) {
    m_eGType = eQWidget;
    m_QWidget = new QWidget;
    return *this;
}
//===============================================
GQt& GQt::createQPushButton(const QString& _name, QWidget* _parent) {
    m_eGType = eQPushButton;
    m_QPushButton = new QPushButton(_parent);
    m_QPushButton->setText(_name);
    return *this;
}
//===============================================
GQt& GQt::createQPushButton(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap, QWidget* _parent) {
    createQPushButton(_name, _parent);
    _QWidgetMap[m_QPushButton] = _key;
    return *this;
}
//===============================================
GQt& GQt::createQCheckBox(const QString& _name, QWidget* _parent) {
    m_eGType = eQCheckBox;
    m_QCheckBox = new QCheckBox(_name, _parent);
    return *this;
}
//===============================================
GQt& GQt::createQCheckBox(const QString& _name, const QString& _key, QMap<QWidget*, QString>& _QWidgetMap, QWidget* _parent) {
    createQCheckBox(_name, _parent);
    _QWidgetMap[m_QCheckBox] = _key;
    return *this;
}
//===============================================
GQt& GQt::createQLabel(const QString& _text, QWidget* _parent) {
    m_eGType = eQLabel;
    m_QLabel = new QLabel(_text, _parent);
    return *this;
}
//===============================================
GQt& GQt::createQLineEdit(QWidget* _parent) {
    m_eGType = eQLineEdit;
    m_QLineEdit = new QLineEdit(_parent);
    return *this;
}
//===============================================
GQt& GQt::createQLineEdit(const QString& _key, QMap<QWidget*, QString>& _QWidgetMap, QWidget* _parent) {
    m_eGType = eQLineEdit;
    m_QLineEdit = new QLineEdit(_parent);
    _QWidgetMap[m_QLineEdit] = _key;
    return *this;
}
//===============================================
GQt& GQt::createQTextEdit(QWidget* _parent) {
    m_eGType = eQTextEdit;
    m_QTextEdit = new QTextEdit(_parent);
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
GQt& GQt::createQSpinBox(QWidget* _parent) {
    m_eGType = eQSpinBox;
    m_QSpinBox = new QSpinBox(_parent);
    return *this;
}
//===============================================
GQt& GQt::createQSlider(QWidget* _parent) {
    m_eGType = eQSlider;
    m_QSlider = new QSlider(_parent);
    return *this;
}
//===============================================
GQt& GQt::createQVBoxLayout(QWidget* _parent) {
    m_eGType = eQVBoxLayout;
    m_QVBoxLayout = new QVBoxLayout(_parent);
    return *this;
}
//===============================================
GQt& GQt::createQHBoxLayout(QWidget* _parent) {
    m_eGType = eQHBoxLayout;
    m_QHBoxLayout = new QHBoxLayout(_parent);
    return *this;
}
//===============================================
GQt& GQt::addWidget(GQt& _widget) {
    getQBoxLayout()->addWidget(_widget.getQWidget());
    return *this;
}
//===============================================
GQt& GQt::addLayout(GQt& _layout) {
    getQBoxLayout()->addLayout(_layout.getQBoxLayout());
    return *this;
}
//===============================================
GQt& GQt::addStretch(int _stretch) {
    getQBoxLayout()->addStretch(_stretch);
    return *this;
}
//===============================================
GQt& GQt::setBuddy(GQt& _widget) {
    if(m_eGType == eQLabel) m_QLabel->setBuddy(_widget.getQWidget());
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
GQt& GQt::setRange(int _min, int _max) {
    if(m_eGType == eQSpinBox) m_QSpinBox->setRange(_min, _max);
    if(m_eGType == eQSlider) m_QSlider->setRange(_min, _max);
    return *this;
}
//===============================================
GQt& GQt::setText(const QString& _text) {
    if(m_eGType == eQLabel) m_QLabel->setText(_text);
    return *this;
}
//===============================================
GQt& GQt::setDefault(bool _ok) {
    if(m_eGType == eQPushButton) m_QPushButton->setDefault(_ok);
    return *this;
}
//===============================================
GQt& GQt::setEnabled(bool _ok) {
    getQWidget()->setEnabled(_ok);
    return *this;
}
//===============================================
GQt& GQt::setValidator(const QString& _pattern, QWidget* _widget) {
	if(m_eGType == eQLineEdit) {
		QRegExp lQRegExp(_pattern);
	    m_QLineEdit->setValidator(new QRegExpValidator(lQRegExp, _widget));
	}
    return *this;
}
//===============================================
GQt& GQt::connectObject(const char* _signal, const QObject* _member, const char* _slot) {
    connect(getQWidget(), _signal, _member, _slot);
    return *this;
}
//===============================================
GQt& GQt::connectObject(const char* _signal, GQt& _member, const char* _slot) {
    connect(getQWidget(), _signal, _member.getQWidget(), _slot);
    return *this;
}
//===============================================
QWidget* GQt::getQWidget() {
    if(m_eGType == eQWidget) return m_QWidget;
    if(m_eGType == eQPushButton) return m_QPushButton;
    if(m_eGType == eQCheckBox) return m_QCheckBox;
    if(m_eGType == eQLabel) return m_QLabel;
    if(m_eGType == eQLineEdit) return m_QLineEdit;
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
QString GQt::getText() {
    QString lData;
    if(m_eGType == eQLineEdit) lData = m_QLineEdit->text();
    if(m_eGType == eQTextEdit) lData = m_QTextEdit->toPlainText();
    return lData;
}
//===============================================
QString GQt::getKey(int _argc, char** _argv, int _index) {
    QString lKey = "default";
    if(_argc > _index) {
        lKey = _argv[_index];
    }
    return lKey;
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
Qt::CaseSensitivity GQt::getCaseSensitivity() {
	Qt::CaseSensitivity lCaseSensitivity;
	if(m_eGType == eQCheckBox) {
		lCaseSensitivity = isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
	}
    return lCaseSensitivity;
}
//===============================================
bool GQt::isEmpty() {
    if(m_eGType == eQLineEdit) return m_QLineEdit->text().isEmpty();
    if(m_eGType == eQTextEdit) return m_QTextEdit->toPlainText().isEmpty();
    return false;
}
//===============================================
bool GQt::isChecked() {
    if(m_eGType == eQCheckBox) return m_QCheckBox->isChecked();
    return false;
}
//===============================================
bool GQt::hasAcceptableInput() {
    if(m_eGType == eQLineEdit) return m_QLineEdit->hasAcceptableInput();
    return false;
}
//===============================================
