//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
#include "GLog.h"
//===============================================
class GWidget : public QWidget {
    Q_OBJECT

public:
    GWidget(QWidget* _parent = 0);
    ~GWidget();

protected:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
