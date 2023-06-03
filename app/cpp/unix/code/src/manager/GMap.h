//===============================================
#ifndef _GMap_
#define _GMap_
//===============================================
#include "GInclude.h"
//===============================================
class GMap : public std::map<GString, GString> {
public:
    GMap();
    ~GMap();

public:
    GString toParams();

protected:
};
//==============================================
#endif
//==============================================
