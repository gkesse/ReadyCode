//===============================================
#ifndef _GPoco2_
#define _GPoco2_
//===============================================
#include "GObject.h"
#include "GString2.h"
//===============================================
class GPoco2 : public GObject {
public:
    GPoco2();
    ~GPoco2();

    void setUri(const GString2& _uri);

    Poco::Net::HTTPResponse& getHeader();
    GString2 getContent() const;

    bool getHttp();

private:
    GString2 m_uri;
    GString2 m_username;
    GString2 m_password;
    GString2 m_content;
    GString2 m_errors;
    Poco::Net::HTTPResponse m_header;
};
//==============================================
#endif
//==============================================
