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
    bool onModule(GSocket* _client);
    //
    void onTest(GSocket* _client);
    void onUser(GSocket* _client);
    void onReq(GSocket* _client);
    void onMaj(GSocket* _client);
    void onMd5(GSocket* _client);
    void onManager(GSocket* _client);
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
