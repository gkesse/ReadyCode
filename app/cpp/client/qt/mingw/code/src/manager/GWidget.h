//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
#include "GLog.h"
#include "GClientUi.h"
//===============================================
class GWidget : public QWidget {
    Q_OBJECT

public:
    GWidget(QWidget* _parent = 0);
    ~GWidget();
    void setClientUi(GClientUi* _clientUi);

protected:
    GLog m_logs;
    GClientUi* m_clientUi;
};
//===============================================
#endif
//===============================================
