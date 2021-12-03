//===============================================
#include "GQtButtonCircle.h"
#include "GQtPicto.h"
//===============================================
GQtButtonCircle::GQtButtonCircle(QWidget* _parent) :
GQtWidget(_parent) {
    m_QPushButton = new QPushButton(_parent);
    m_QPushButton->setCursor(Qt::PointingHandCursor);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(m_QPushButton);
    lMainLayout->setMargin(0);
    lMainLayout->setAlignment(Qt::AlignCenter);

    setLayout(lMainLayout);

    m_bgColor = "black";
    m_fgColor = "white";
    m_hoverColor = "gray";
    m_fontFamily = "FontAwesome";
    m_fontSize = 25;
    m_iconSize = 50;
    m_text = QChar(fa::user);

    updateView();

    connect(m_QPushButton, SIGNAL(clicked()), this, SIGNAL(clicked()));
}
//===============================================
GQtButtonCircle::~GQtButtonCircle() {

}
//===============================================
void GQtButtonCircle::setBgColor(const QString& _bgColor) {
    m_bgColor = _bgColor;
    updateView();
}
//===============================================
void GQtButtonCircle::setFgColor(const QString& _fgColor) {
    m_fgColor = _fgColor;
    updateView();
}
//===============================================
void GQtButtonCircle::setHoverColor(const QString& _hoverColor) {
    m_hoverColor = _hoverColor;
    updateView();
}
//===============================================
void GQtButtonCircle::setFontFamily(const QString& _fontFamily) {
    m_fontFamily = _fontFamily;
    updateView();
}
//===============================================
void GQtButtonCircle::setFontSize(int _fontSize) {
    m_fontSize = _fontSize;
    updateView();
}
//===============================================
void GQtButtonCircle::setIconSize(int _iconSize) {
    m_iconSize = _iconSize;
    updateView();
}
//===============================================
void GQtButtonCircle::setIcon(int _icon) {
    m_text = QChar(_icon);
    m_fontFamily = "FontFamily";
    updateView();
}
//===============================================
void GQtButtonCircle::setText(const QString& _text) {
    m_text = _text;
    if(m_fontFamily == "FontFamily") {
        m_fontFamily = "arial";
    }
    updateView();
}
//===============================================
void GQtButtonCircle::updateView() {
    m_QPushButton->setText(m_text);
    m_QPushButton->setStyleSheet(QString(""
            "QPushButton {"
            "background-color:%1;"
            "color:%2;"
            "font-family:%3;"
            "font-size:%4px;"
            "min-width:%5px;"
            "min-height:%5px;"
            "border-radius:%6px;"
            "}"
            "QPushButton:hover {"
            "background-color:%7;"
            "}"
            "QPushButton:pressed {"
            "background-color:%1;"
            "}"
            "").arg(m_bgColor).arg(m_fgColor).arg(m_fontFamily)
            .arg(m_fontSize).arg(m_iconSize).arg(m_iconSize/2)
            .arg(m_hoverColor));
}
//===============================================
