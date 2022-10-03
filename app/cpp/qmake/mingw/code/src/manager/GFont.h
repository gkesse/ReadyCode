//===============================================
#ifndef _GFont_
#define _GFont_
//===============================================
#include "GObject.h"
//===============================================
#define GFONT       GFont::Instance()
#define GFONT_LOAD  GFONT->loadFont
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
