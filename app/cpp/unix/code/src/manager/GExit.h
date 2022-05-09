//===============================================
#ifndef _GExit_
#define _GExit_
//===============================================
#include "GObject.h"
//===============================================
class GExit : public GObject {
public:
    typedef void (*GEXIT_CB)();

public:
    GExit();
    ~GExit();
    void setCallback(void* _onExit);
    //
    static void onExit();
};
//==============================================
#endif
//==============================================
