//===============================================
#ifndef _GMd5_
#define _GMd5_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GMd5 : public GModule {
public:
    GMd5();
    ~GMd5();
    std::string serialize(const std::string& _code = "md5") const;
    void deserialize(const std::string& _data, const std::string& _code = "md5");
    bool onModule(GSocket* _client);
    bool onEncodeData(GSocket* _client);
    std::string encodeData(const std::string& _data) const;

private:
    std::string m_dataIn;
    std::string m_dataOut;
};
//==============================================
#endif
//==============================================
