//===============================================
#ifndef _GFont2_
#define _GFont2_
//===============================================
#include "GObject2.h"
//===============================================
#define GFONTI      GFont2::Instance()
#define GFONT_LOAD  GFONTI->loadFont
//===============================================
class GFont2 : public GObject2 {
	Q_OBJECT

public:
    GFont2(QObject* _parent = 0);
    ~GFont2();
    static GFont2* Instance();
    bool loadFont();

private:
    static GFont2* m_instance;
};
//==============================================
#endif
//==============================================
