//===============================================
#ifndef _GImageLoad_
#define _GImageLoad_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GImageLoad : public GOpenCVUi {
    Q_OBJECT
    
public:
    GImageLoad(QObject* parent = 0);
    virtual ~GImageLoad();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
