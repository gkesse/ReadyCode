//===============================================
#ifndef _GVideoCamera_
#define _GVideoCamera_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GVideoCamera : public GOpenCVUi {
    Q_OBJECT
    
public:
    GVideoCamera(QObject* parent = 0);
    virtual ~GVideoCamera();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
