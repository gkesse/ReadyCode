//===============================================
#ifndef _GVideoTrackbar_
#define _GVideoTrackbar_
//===============================================
#include "GOpenCVUi.h"
//===============================================
class GVideoTrackbar : public GOpenCVUi {
    Q_OBJECT
    
public:
    GVideoTrackbar(QObject* parent = 0);
    virtual ~GVideoTrackbar();
    void run(int argc, char** argv);
    static void onTrackbarSlide( int pos, void* params );
};
//==============================================
#endif
//==============================================
