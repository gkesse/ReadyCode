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
    ~GCode();
    //
    void createRequest(const std::string& _module, const std::string& _method);
    std::string getModule();
    std::string getMethod();
    //
    void setCode(const std::string& _code);
    bool hasCode(const std::string& _code);
    bool hasCode(const std::string& _code, const std::string& _key);
    void createCode();
    void createCode(const std::string& _code);
    void createCode(const std::string& _code, const std::string& _key, const std::string& _value);
    void createMap(const std::string& _code, const std::string& _key, const std::string& _value);
    //
    std::string getItem(const std::string& _code, const std::string& _key);
    std::string getItem(const std::string& _code, int _index, const std::string& _key);
    int countItem(const std::string& _code, const std::string& _key);
};
//==============================================
#endif
//==============================================