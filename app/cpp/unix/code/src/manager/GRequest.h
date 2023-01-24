//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GObject.h"
//===============================================
class GRequest : public GObject {
public:
    GRequest();
    ~GRequest();

    void setRequest(const GString& _request);
    GString getResponse() const;

    bool run();
    bool runGet();
    bool runPost();
    bool runApp();
    bool runPostRequest();
    bool runHttp();

private:
    static const int NBR_LINE_MAX = 20;

    GString m_request;
    GString m_requestBody;
    GString m_response;
    GString m_responseBody;
    GString m_contentType;
    int m_status;
};
//==============================================
#endif
//==============================================
