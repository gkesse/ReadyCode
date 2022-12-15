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
    void initStyle();
    bool loadStyle();

private:
    static GStyle* m_instance;
    GString m_styleFile;
};
//==============================================
#endif
//==============================================
