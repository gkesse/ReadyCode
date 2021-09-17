//===============================================
#ifndef _GProWindow_
#define _GProWindow_
//===============================================
#include "GProUi.h"
//===============================================
class GProWindow : public GProUi {
    Q_OBJECT
    
public:
    GProWindow(QWidget* parent = 0);
    ~GProWindow();
};
//==============================================
#endif
//==============================================
