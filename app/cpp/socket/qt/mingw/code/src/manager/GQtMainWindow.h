//===============================================
#ifndef _GQtMainWindow_
#define _GQtMainWindow_
//===============================================
#include "GInclude.h"
//===============================================
class GQtMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GQtMainWindow(QWidget* _parent = 0);
    ~GQtMainWindow();
};
//==============================================
#endif
//==============================================
