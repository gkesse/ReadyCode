//===============================================
#ifndef _GImagePixel_
#define _GImagePixel_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GImagePixel : public GOpenCVUi {
    Q_OBJECT
    
public:
    GImagePixel(QObject* parent = 0);
    virtual ~GImagePixel();
    void run(int argc, char** argv);
};
//==============================================
#endif
//==============================================
