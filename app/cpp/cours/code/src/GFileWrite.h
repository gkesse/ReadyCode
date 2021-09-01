//===============================================
#ifndef _GFileStorage_
#define _GFileStorage_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GFileWrite : public GOpenCVUi {
    Q_OBJECT
    
public:
    GFileWrite(QObject* parent = 0);
    virtual ~GFileWrite();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
