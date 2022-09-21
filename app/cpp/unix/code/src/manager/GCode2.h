//===============================================
#ifndef _GCode2_
#define _GCode2_
//===============================================
#include "GXml2.h"
//===============================================
class GCode2 : public GXml2 {
public:
    GCode2();
    ~GCode2();

    bool createCode();
    bool createCode(const GString2& _code);

    bool getCode();
    bool getCode(const GString2& _code);
    bool getCode(const GString2& _code, const GString2& _key);

    GString2 getData(const GString2& _code, const GString2& _key);

    bool addData(const GString2& _code, const GString2& _key, const GString2& _value , bool _isCData = false);
    bool addData(const GString2& _code, const std::vector<GObject2*>& _map);

    GString2 toData();
};
//==============================================
#endif
//==============================================
