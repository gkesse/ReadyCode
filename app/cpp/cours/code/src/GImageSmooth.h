//===============================================
#ifndef _GImageSmooth_
#define _GImageSmooth_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GImageSmooth : public GOpenCVUi {
    Q_OBJECT
    
public:
    GImageSmooth(QObject* parent = 0);
    virtual ~GImageSmooth();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
