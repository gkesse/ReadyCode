//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
class GCode : public GXml {
public:
    GCode();
    GCode(const std::string& _code);
    GCode(const std::string& _version, const std::string& _nodeRoot);
    ~GCode();
    //
    void createReq(const std::string& _module, const std::string& _method);
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
    void createCode();
    void createCode(const std::string& _code);
    void createCode(const std::string& _code, const std::string& _key, const std::string& _value, bool _isCData = false);
    void createCode(const std::string& _code, const std::string& _key, const int _value, bool _isCData = false);
    void createMap(const std::string& _code, const std::string& _key, int _value, int _index, bool _isCData = false);
    void createMap(const std::string& _code, int _value, int _index, bool _isCData = false);
    void createMap(const std::string& _code, const std::string& _value, int _index, bool _isCData = false);
    void createMap(const std::string& _code, const std::string& _key, const std::string& _value, int _index, bool _isCData = false);
    //
    void getCodeNode(const std::string& _code);
    //
    std::string getItem(const std::string& _code, const std::string& _key);
    std::string getItem(const std::string& _code, int _index, const std::string& _key);
    int countItem(const std::string& _code, const std::string& _key);
    //
    void loadCode(const std::string& _code);
    //
    std::string toStringCode(const std::string& _code);
};
//==============================================
#endif
//==============================================
