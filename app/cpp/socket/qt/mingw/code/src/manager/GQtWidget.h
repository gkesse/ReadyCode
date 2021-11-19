//===============================================
#ifndef _GQtWidget_
#define _GQtWidget_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GQtWidget : public QFrame {
    Q_OBJECT

public:
    GQtWidget(QWidget* _parent = 0);
    ~GQtWidget();
    static GQtWidget* Create(const QString& _key);

protected:
    QMap<QWidget*, QString> m_QWidgetMap;
};
//==============================================
#endif
//==============================================
