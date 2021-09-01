//===============================================
#ifndef _GImageBlend_
#define _GImageBlend_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GImageBlend : public GOpenCVUi {
    Q_OBJECT
    
public:
    GImageBlend(QObject* parent = 0);
    virtual ~GImageBlend();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
