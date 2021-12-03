//===============================================
#ifndef _GQtTeamsBox_
#define _GQtTeamsBox_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtButtonCircle;
class GQtTextEdit;
//===============================================
class GQtTeamsBox : public GQtWidget {
    Q_OBJECT

public:
    GQtTeamsBox(QWidget* _parent = 0);
    ~GQtTeamsBox();
    void setIndex(int _index);
    void setIndexIcon(int _index, int _icon);
    void setIndexText(int _index, const QString& _text);
    void setIcon(int _icon);
    void setText(const QString& _text);


protected:
    void updateView();

protected:
    GQtButtonCircle* m_iconTR;
    GQtButtonCircle* m_iconTL;
    GQtButtonCircle* m_iconBR;
    GQtButtonCircle* m_iconBL;
    GQtTextEdit* m_message;
    QList<QWidget*> m_iconList;
    int m_index;
    int m_icon;
    QString m_text;
    int m_type;
};
//==============================================
#endif
//==============================================
