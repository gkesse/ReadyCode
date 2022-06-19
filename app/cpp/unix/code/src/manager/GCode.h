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
    void createReq(const std::string& _module, const std::string& _method);
    bool hasCode();
    bool hasCode(const std::string& _code);
    bool hasCode(const std::string& _code, const std::string& _key);
    bool createCode(const std::string& _code);
    bool addData(const std::string& _code, const std::string& _key, const std::string& _value, bool _isCData = false);
    bool addData(const std::string& _code, const std::string& _key, int _value, bool _isCData = false);
    bool addData(const std::string& _code, const std::vector<std::string>& _datas, bool _isCData = false);
    bool addData(const std::string& _code, std::vector<GObject*>& _datas);
    bool getCode(const std::string& _code);
    bool getCode(const std::string& _code, const std::string& _key);
    //
    std::string getItem(const std::string& _code, const std::string& _key);
    std::string getItem(const std::string& _code, const std::string& _key, int _index);
    bool getItem(const std::string& _code, const std::vector<GObject*>& _datas);
    std::string getMap(const std::string& _code, int _index);
    int countItem(const std::string& _code);
    //
    bool loadCode(const std::string& _data, bool _isRoot = true);
    //
    std::string toStringCode(const std::string& _code);
    std::string toStringData();
};
//==============================================
#endif
//==============================================
