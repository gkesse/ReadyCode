//===============================================
#ifndef _GSocketReadyApp_
#define _GSocketReadyApp_
//===============================================
#include "GSocket.h"
//===============================================
class GSocketReadyApp : public GSocket {
public:
    GSocketReadyApp();
    ~GSocketReadyApp();

    GString getRequest() const;
    bool addResponse(const GString& _data);

protected:
    void initReadyApp();
    bool runThreadCB();
    bool runRequest();
    bool readMethod();
    bool isValidRequest();
    bool isValidRequest(const GSocketReadyApp& _obj);
    bool readHeader();
    bool readRequest();
    bool analyzeRequest();
    bool integrateErrors();
    bool createResponse();
    bool createData();

protected:
    GString m_apiKey;
    GString m_apiKeyProd;
    GString m_apiKeyTest;
    GString m_apiUsername;
    GString m_apiPassword;

    int m_dataSize;
    int m_headerSize;
    int m_diffSize;

    GString m_request;
    GString m_response;
    std::shared_ptr<GCode> m_domResponse;
};
//==============================================
#endif
//==============================================