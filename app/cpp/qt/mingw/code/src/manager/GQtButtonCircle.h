//===============================================
#ifndef _GQtButtonCircle_
#define _GQtButtonCircle_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtButtonCircle : public GQtWidget {
    Q_OBJECT

public:
    GQtButtonCircle(QWidget* _parent = 0);
    ~GQtButtonCircle();
    void setBgColor(const QString& _bgColor);
    void setFgColor(const QString& _fgColor);
    void setHoverColor(const QString& _hoverColor);
    void setFontFamily(const QString& _fontFamily);
    void setFontSize(int _fontSize);
    void setIconSize(int _iconSize);
    void setIcon(int _icon);
    void setText(const QString& _text);

protected:
    void updateView();

protected:
    QPushButton* m_QPushButton;
    QString m_fgColor;
    QString m_bgColor;
    QString m_hoverColor;
    QString m_fontFamily;
    int m_fontSize;
    int m_iconSize;
    QString m_text;
};
//==============================================
#endif
//==============================================
