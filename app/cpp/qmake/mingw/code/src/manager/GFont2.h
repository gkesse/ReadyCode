//===============================================
#ifndef _GFont2_
#define _GFont2_
//===============================================
#include "GObject.h"
//===============================================
#define GFONTI      GFont2::Instance()
#define GFONT_LOAD  GFONTI->loadFont
//===============================================
class GFont2 : public GObject {
public:
    GFont2();
    ~GFont2();
    static GFont2* Instance();
    bool loadFont();

private:
    static GFont2* m_instance;
};
//==============================================
#endif
//==============================================
