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
    void createRequest(const std::string& _module, const std::string& _method);
    std::string getModule();
    std::string getMethod();
    std::string getParam(const std::string& _param);
    std::string getSession(const std::string& _param);
    bool isValidReq();
    //
    bool hasCode(const std::string& _code);
    bool hasCode(const std::string& _code, const std::string& _key);
    bool hasCode(const std::string& _code, int _index);
    bool hasCode(const std::string& _code, const std::string& _key, int _index);
    bool hasMap(const std::string& _code);
    bool createCode(const std::string& _code);
    bool addData(const std::string& _code, const std::string& _key, const std::string& _value, bool _isCData = false);
    bool getCode(const std::string& _code);
    bool getCode(const std::string& _code, const std::string& _key);
    void createCode(const std::string& _code, const std::string& _key, const int _value, bool _isCData = false);
    //
    void getCodeNode(const std::string& _code);
    //
    std::string getItem(const std::string& _code, const std::string& _key);
    std::string getItem(const std::string& _code, const std::string& _key, int _index);
    int countItem(const std::string& _code);
    //
    bool loadCode(const std::string& _data, bool _isRoot = true);
    //
    std::string toStringCode(const std::string& _code);
};
//==============================================
#endif
//==============================================
