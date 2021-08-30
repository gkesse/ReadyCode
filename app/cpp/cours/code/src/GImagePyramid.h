//===============================================
#ifndef _GImagePyramid_
#define _GImagePyramid_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GImagePyramid : public GOpenCVUi {
    Q_OBJECT
    
public:
    GImagePyramid(QObject* parent = 0);
    virtual ~GImagePyramid();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
