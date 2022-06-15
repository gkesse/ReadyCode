//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GMaster : public GModule {
public:
    GMaster();
    ~GMaster();
    //
    std::string serialize(const std::string& _code = "server") const;
    void deserialize(const std::string& _data, const std::string& _code = "server");
    //
    void onModule(GSocket* _client);
    //
    void onModuleTest(GSocket* _client);
    void onModuleUser(GSocket* _client);
    void onModuleReq(GSocket* _client);
    void onModuleMaj(GSocket* _client);
    void onModuleMd5(GSocket* _client);
    //
    bool isValidXml(const std::string& _data);
    bool isValidReq();

private:
    bool m_validateXml;
    bool m_validateReq;
};
//==============================================
#endif
//==============================================
