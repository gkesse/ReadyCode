//===============================================
#ifndef _GPoco_
#define _GPoco_
//===============================================
#include "GObject.h"
//===============================================
class GPoco : public GObject {
public:
    GPoco();
    ~GPoco();

    void setUri(const GString& _uri);

    Poco::Net::HTTPResponse& getHeader();
    GString getContent() const;

    bool getHttp();

private:
    GString m_uri;
    GString m_username;
    GString m_password;
    GString m_content;
    GString m_errors;
    Poco::Net::HTTPResponse m_header;
};
//==============================================
#endif
//==============================================
