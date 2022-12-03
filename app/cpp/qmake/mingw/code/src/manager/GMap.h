//===============================================
#ifndef _GMap_
#define _GMap_
//===============================================
#include "GCode.h"
//===============================================
class GMap : public GCode {
public:
    GMap();
    GMap(const GString& _data);
    ~GMap();

    void addObject(const GString& _key, const GString& _obj, const GString& _code = "map");
    GString getObject(const GString& _key, const GString& _code = "map");
};
//==============================================
#endif
//==============================================
