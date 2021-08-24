//===============================================
#ifndef _GDifferentiation_
#define _GDifferentiation_
//===============================================
#include "GGslUi.h"
//===============================================
class GDifferentiation : public GGslUi {
    Q_OBJECT
    
public:
    GDifferentiation(QWidget* parent = 0);
    virtual ~GDifferentiation();
    void resize();
    static double onFunction(double x, void* params);
};
//==============================================
#endif
//==============================================
