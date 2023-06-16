//===============================================
#ifndef _GMainWindow_
#define _GMainWindow_
//===============================================
#include "GInclude.h"
#include "GLog.h"
//===============================================
class GMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GMainWindow(QWidget* _parent = 0);
    ~GMainWindow();

protected:
    GLog m_logs;
};
//===============================================
#endif
//===============================================
