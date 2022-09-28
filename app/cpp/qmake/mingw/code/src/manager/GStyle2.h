//===============================================
#ifndef _GStyle2_
#define _GStyle2_
//===============================================
#include "GObject2.h"
//===============================================
#define GSTYLEI         GStyle2::Instance()
#define GSTYLE_LOAD     GSTYLEI->loadStyle
//===============================================
class GStyle2 : public GObject2 {
public:
    GStyle2();
    ~GStyle2();
    static GStyle2* Instance();
    bool loadStyle();
    bool loadStyle(const GString& _filename);

private:
    static GStyle2* m_instance;
};
//==============================================
#endif
//==============================================
