//===============================================
#ifndef _GVideoWrite_
#define _GVideoWrite_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GVideoWrite : public GOpenCVUi {
    Q_OBJECT
    
public:
    GVideoWrite(QObject* parent = 0);
    virtual ~GVideoWrite();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
