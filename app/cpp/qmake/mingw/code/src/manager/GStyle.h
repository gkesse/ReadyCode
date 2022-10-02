//===============================================
#ifndef _GStyle_
#define _GStyle_
//===============================================
#include "GObject.h"
//===============================================
#define GSTYLEI         GStyle::Instance()
#define GSTYLE_LOAD     GSTYLEI->loadStyle
//===============================================
class GStyle : public GObject {
public:
    GStyle();
    ~GStyle();
    static GStyle* Instance();
    bool loadStyle();
    bool loadStyle(const GString& _filename);

private:
    static GStyle* m_instance;
};
//==============================================
#endif
//==============================================
