//===============================================
#ifndef _GQtSpreadWindow_
#define _GQtSpreadWindow_
//===============================================
#include "GQtMainWindow.h"
//===============================================
class GQtSpreadWindow : public GQtMainWindow {
    Q_OBJECT

public:
    GQtSpreadWindow(QWidget* _parent = 0);
    ~GQtSpreadWindow();
    void createActions();
};
//==============================================
#endif
//==============================================
