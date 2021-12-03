//===============================================
#ifndef _GQtTextEdit_
#define _GQtTextEdit_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtTextEdit : public GQtWidget {
    Q_OBJECT

public:
    GQtTextEdit(QWidget* _parent = 0);
    ~GQtTextEdit();
    void setBgColor(const QString& _bgColor);
    void setFgColor(const QString& _fgColor);
    void setHoverColor(const QString& _hoverColor);
    void setFontFamily(const QString& _fontFamily);
    void setFontSize(int _fontSize);
    void setMaxHeight(int _maxHeight);
    void setBorderRadius(int _borderRadius);
    void setPadding(int _padding);
    QString getText() const;

protected:
    void updateView();

protected:
    QTextEdit* m_QTextEdit;
    QString m_fgColor;
    QString m_bgColor;
    QString m_hoverColor;
    QString m_fontFamily;
    int m_fontSize;
    int m_maxHeight;
    int m_borderRadius;
    int m_padding;
};
//==============================================
#endif
//==============================================
