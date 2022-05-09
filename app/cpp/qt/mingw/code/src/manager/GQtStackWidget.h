//===============================================
#ifndef _GQtStackWidget_
#define _GQtStackWidget_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtStackWidget : public GQtWidget {
    Q_OBJECT

public:
    GQtStackWidget(QWidget* _parent = 0);
    ~GQtStackWidget();
    void addWidget(const QString& _key, QWidget* _widget);
    bool setWidget(const QString& _key);

private:
    QStackedWidget* m_widgetMap;
    QMap<QString, int> m_widgetId;
};
//==============================================
#endif
//==============================================
