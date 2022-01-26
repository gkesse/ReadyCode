//===============================================
#ifndef _GQtWidget_
#define _GQtWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GQtXml;
//===============================================
class GQtWidget : public QFrame {
    Q_OBJECT

public:
    GQtWidget(QWidget* _parent = 0);
    ~GQtWidget();
    QPushButton* createButtonIcon(const QString& _text, QPushButton** _chevron);
    QLineEdit* createLineEditIcon(QPushButton** _icon);

protected:
    QSharedPointer<GQtXml> m_dom;
};
//==============================================
#endif
//==============================================
