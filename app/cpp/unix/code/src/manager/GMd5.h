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
    GString serialize(const GString& _code = "md5") const;
    void deserialize(const GString& _data, const GString& _code = "md5");
    bool onModule(GSocket* _client);
    bool onEncodeData(GSocket* _client);
    GString encodeData(const GString& _data) const;

private:
    GString m_dataIn;
    GString m_dataOut;
};
//==============================================
#endif
//==============================================
