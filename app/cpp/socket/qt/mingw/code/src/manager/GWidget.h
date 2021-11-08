//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GWidget : public QFrame {
	Q_OBJECT

public:
    GWidget(QWidget* _parent = 0);
    ~GWidget();
    static GWidget* Create(const QString& _key);

public slots:
    virtual void onEvent();

protected:
    QMap<QWidget*, QString> m_widgetMap;
};
//==============================================
#endif
//==============================================
