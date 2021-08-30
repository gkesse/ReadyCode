//===============================================
#ifndef _GImageCanny_
#define _GImageCanny_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GImageCanny : public GOpenCVUi {
    Q_OBJECT
    
public:
    GImageCanny(QObject* parent = 0);
    virtual ~GImageCanny();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
