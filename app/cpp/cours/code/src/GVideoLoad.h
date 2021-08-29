//===============================================
#ifndef _GVideoLoad_
#define _GVideoLoad_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GVideoLoad : public GOpenCVUi {
    Q_OBJECT
    
public:
    GVideoLoad(QObject* parent = 0);
    virtual ~GVideoLoad();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
