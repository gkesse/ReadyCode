//===============================================
#include "GQtTextEdit.h"
//===============================================
GQtTextEdit::GQtTextEdit(QWidget* _parent) :
GQtWidget(_parent) {
    m_QTextEdit = new QTextEdit(_parent);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(m_QTextEdit);
    lMainLayout->setMargin(0);
    lMainLayout->setAlignment(Qt::AlignCenter);

    setLayout(lMainLayout);

    m_bgColor = "black";
    m_fgColor = "white";
    m_hoverColor = "black";
    m_fontFamily = "arial";
    m_fontSize = 16;
    m_maxHeight = 150;
    m_borderRadius = 10;
    m_padding = 10;

    updateView();
}
//===============================================
GQtTextEdit::~GQtTextEdit() {

}
//===============================================
void GQtTextEdit::setBgColor(const QString& _bgColor) {
    m_bgColor = _bgColor;
    updateView();
}
//===============================================
void GQtTextEdit::setFgColor(const QString& _fgColor) {
    m_fgColor = _fgColor;
    updateView();
}
//===============================================
void GQtTextEdit::setHoverColor(const QString& _hoverColor) {
    m_hoverColor = _hoverColor;
    updateView();
}
//===============================================
void GQtTextEdit::setFontFamily(const QString& _fontFamily) {
    m_fontFamily = _fontFamily;
    updateView();
}
//===============================================
void GQtTextEdit::setFontSize(int _fontSize) {
    m_fontSize = _fontSize;
    updateView();
}
//===============================================
void GQtTextEdit::setMaxHeight(int _maxHeight) {
    m_maxHeight = _maxHeight;
    updateView();
}
//===============================================
void GQtTextEdit::setBorderRadius(int _borderRadius) {
    m_borderRadius = _borderRadius;
    updateView();
}
//===============================================
void GQtTextEdit::setPadding(int _padding) {
    m_padding = _padding;
    updateView();
}
//===============================================
QString GQtTextEdit::getText() const {
    return m_QTextEdit->toPlainText();
}
//===============================================
void GQtTextEdit::updateView() {
    m_QTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "background-color:%1;"
            "color:%2;"
            "font-family:%3;"
            "font-size:%4px;"
            "max-height:%5px;"
            "border-radius:%6px;"
            "padding:%7px;"
            "}"
            "QTextEdit:hover {"
            "background-color:%8;"
            "}"
            "").arg(m_bgColor).arg(m_fgColor).arg(m_fontFamily)
            .arg(m_fontSize).arg(m_maxHeight).arg(m_borderRadius)
            .arg(m_padding).arg(m_hoverColor));
}
//===============================================
