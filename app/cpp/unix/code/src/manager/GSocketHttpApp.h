//===============================================
#ifndef _GSocketHttpApp_
#define _GSocketHttpApp_
//===============================================
#include "GSocket.h"
//===============================================
class GSocketHttpApp : public GSocket {
public:
    GSocketHttpApp();
    ~GSocketHttpApp();

protected:
    bool runThreadCB();
    bool runRequest();
    bool readMethod();
    bool isValidRequest();
    bool readHeader();
    bool readRequest();
    bool analyzeRequest();
    bool integrateErrors();
    bool createResponse();
    bool createData();
    bool isLine(char _char, int& _index) const;
    bool isHeader(char _char, int& _index) const;

protected:
    GString m_method;
    GString m_url;
    GString m_version;
    GString m_reason;
    int m_status;

    GString m_hostname;
    int m_port;

    GString m_connection;

    GString m_contentType;
    int m_contentLength;

    GString m_request;
    GString m_content;

    int m_dataSize;
    int m_headerSize;
    int m_diffSize;

};
//==============================================
#endif
//==============================================
