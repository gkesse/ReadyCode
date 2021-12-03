//===============================================
#include "GQt.h"
//===============================================
GQt* GQt::m_instance = 0;
//===============================================
GQt::GQt() {

}
//===============================================
GQt::~GQt() {

}
//===============================================
GQt* GQt::Instance() {
    if(m_instance == 0) {
        m_instance = new GQt;
    }
    return m_instance;
}
//===============================================
QTextEdit* GQt::createQTextEdit(QWidget* _parent) {
    QTextEdit* lQTextEdit = new QTextEdit(_parent);
    lQTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "background-color:black;"
            "color:white;"
            "font-family:courier new;"
            "font-size:16px;"
            "}"
            ""));
    return lQTextEdit;
}
//===============================================
QPushButton* GQt::createButtonCircle(QWidget* _parent) {
    QPushButton* lQPushButton = new QPushButton(_parent);
    lQPushButton->setText("1");
    lQPushButton->setStyleSheet(QString(""
            "QPushButton {"
            "background-color:black;"
            "color:white;"
            "font-family:arial;"
            "font-size:25px;"
            "width:50px;"
            "height:50px;"
            "border-radius:50%;"
            "}"
            ""));
    return lQPushButton;
}
//===============================================
GQt& GQt::addSpacer(QVBoxLayout* _QVBoxLayout) {
    QSpacerItem* lQSpacerItem = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    _QVBoxLayout->addSpacerItem(lQSpacerItem);
    return *this;
}
//===============================================
GQt& GQt::addSpacer(QHBoxLayout* _QHBoxLayout) {
    QSpacerItem* lQSpacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    _QHBoxLayout->addSpacerItem(lQSpacerItem);
    return *this;
}
//===============================================
GQt& GQt::addVSpacer(QGridLayout* _QGridLayout, int _row, int _column, int _rowSpan, int _columnSpan, Qt::Alignment _alignment) {
    QSpacerItem* lQSpacerItem = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    _QGridLayout->addItem(lQSpacerItem, _row, _column, _rowSpan, _columnSpan, _alignment);
    return *this;
}
//===============================================
GQt& GQt::addHSpacer(QGridLayout* _QGridLayout, int _row, int _column, int _rowSpan, int _columnSpan, Qt::Alignment _alignment) {
    QSpacerItem* lQSpacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    _QGridLayout->addItem(lQSpacerItem, _row, _column, _rowSpan, _columnSpan, _alignment);
    _QGridLayout->setColumnStretch(_column, 1);
    return *this;
}
//===============================================
GQt& GQt::setValidator(QLineEdit* _QLineEdit, QString _pattern, QWidget* _parent) {
    QRegExp lQRegExp(_pattern);
    _QLineEdit->setValidator(new QRegExpValidator(lQRegExp, _parent));
    return *this;
}
//===============================================
GQt& GQt::setEnabled(QDialogButtonBox* _QDialogButtonBox, QDialogButtonBox::StandardButton _button, bool _ok) {
    _QDialogButtonBox->button(_button)->setEnabled(_ok);
    return *this;
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
Qt::CaseSensitivity GQt::getCaseSensitivity(QCheckBox* _QCheckBox) {
    Qt::CaseSensitivity lCaseSensitivity =  Qt::CaseInsensitive;
    if(_QCheckBox->isChecked()) {
        lCaseSensitivity =  Qt::CaseSensitive;
    }
    return lCaseSensitivity;
}
//===============================================
bool GQt::isEmpty(QLineEdit* _QLineEdit) {
    return _QLineEdit->text().isEmpty();
}
//===============================================
bool GQt::isEmpty(QTextEdit* _QTextEdit) {
    return _QTextEdit->toPlainText().isEmpty();
}
//===============================================
