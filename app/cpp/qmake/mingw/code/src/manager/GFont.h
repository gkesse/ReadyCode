//===============================================
#ifndef _GFont_
#define _GFont_
//===============================================
#include "GObject.h"
//===============================================
#define GFONTI      GFont2::Instance()
#define GFONT_LOAD  GFONTI->loadFont
//===============================================
class GFont : public GObject {
public:
    GFont();
    ~GFont();
    static GFont* Instance();
    bool loadFont();

private:
    static GFont* m_instance;
};
//==============================================
#endif
//==============================================
