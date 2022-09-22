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
    bool createCode(const GString& _code);
    bool createRequest(const GString& _module, const GString& _method);

    bool loadData(const GString& _data);

    bool getCode();
    bool getCode(const GString& _code);
    bool getCode(const GString& _code, const GString& _key);
    bool getMap(const GString& _code, int _index);

    GString getData(const GString& _code, const GString& _key);
    bool getData(const GString& _code, std::vector<GObject2*>& _map, GObject2* _obj);

    bool addData(const GString& _code, const GString& _key, const GString& _value , bool _isCData = false);
    bool addData(const GString& _code, const std::vector<GObject2*>& _map);

    int countMap(const GString& _code);

    GString toData();
};
//==============================================
#endif
//==============================================
