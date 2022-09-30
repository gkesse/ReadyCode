//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
class GCode : public GXml {
public:
    GCode();
    ~GCode();
    //
    void createReq(const GString& _module, const GString& _method);
    bool hasCode();
    bool hasCode(const GString& _code);
    bool hasCode(const GString& _code, const GString& _key);
    bool createCode(const GString& _code);
    bool addData(const GString& _code, const GString& _key, const GString& _value, bool _isCData = false);
    bool addData(const GString& _code, const GString& _key, int _value, bool _isCData = false);
    bool addData(const GString& _code, const std::vector<GString>& _datas, bool _isCData = false);
    bool addData(const GString& _code, const std::vector<GObject*>& _datas);
    bool getCode(const GString& _code);
    bool getCode(const GString& _code, const GString& _key);
    //
    GString getItem(const GString& _code, const GString& _key);
    GString getItem(const GString& _code, const GString& _key, int _index);
    bool getItem(const GString& _code, std::vector<GObject*>& _datas, GObject* _obj);
    GString getMap(const GString& _code, int _index);
    int countItem(const GString& _code);
    //
    bool loadCode(const GString& _data, bool _isRoot = true);
    //
    GString toStringCode(const GString& _code);
    GString toStringData();
};
//==============================================
#endif
//==============================================
