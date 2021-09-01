//===============================================
#ifndef _GVideoCodec_
#define _GVideoCodec_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GVideoCodec : public GOpenCVUi {
    Q_OBJECT
    
public:
    GVideoCodec(QObject* parent = 0);
    virtual ~GVideoCodec();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
