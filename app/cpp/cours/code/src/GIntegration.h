//===============================================
#ifndef _GIntegration_
#define _GIntegration_
//===============================================
#include "GGslUi.h"
//===============================================
class GIntegration : public GGslUi {
    Q_OBJECT
    
public:
    GIntegration(QWidget* parent = 0);
    virtual ~GIntegration();
    void resize();
    static double onFunction(double x, void* params);
};
//==============================================
#endif
//==============================================
