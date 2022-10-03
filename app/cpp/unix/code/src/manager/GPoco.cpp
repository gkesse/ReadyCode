//===============================================
#include "GPoco.h"
#include "GLog.h"
//===============================================
GPoco::GPoco()
: GObject() {

}
//===============================================
GPoco::~GPoco() {

}
//===============================================
void GPoco::setUri(const GString& _uri) {
    m_uri = _uri;
}
//===============================================
Poco::Net::HTTPResponse& GPoco::getHeader() {
    return m_header;
}
//===============================================
GString GPoco::getContent() const {
    return m_content;
}
//===============================================
bool GPoco::getHttp() {
    if(m_uri.isEmpty()) return false;
    try {
        Poco::URI lUri(m_uri.c_str());
        GString lPath(lUri.getPathAndQuery());
        if(lPath.isEmpty()) lPath = "/";
        std::string lUsername;
        std::string lPassword;
        std::string lContent;
        Poco::Net::HTTPCredentials::extractCredentials(lUri, lUsername, lPassword);
        m_username = lUsername;
        m_password = lPassword;
        Poco::Net::HTTPCredentials lCredentials(m_username.c_str(), m_password.c_str());
        Poco::Net::HTTPClientSession lSession(lUri.getHost(), lUri.getPort());
        Poco::Net::HTTPRequest lRequest(Poco::Net::HTTPRequest::HTTP_GET, lPath.c_str(), Poco::Net::HTTPMessage::HTTP_1_1);
        lSession.sendRequest(lRequest);
        std::istream& lResult = lSession.receiveResponse(m_header);

        if (m_header.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {
            Poco::StreamCopier::copyToString(lResult, lContent);
            m_content = lContent;
            return true;
        }
        else {
            Poco::NullOutputStream null;
            Poco::StreamCopier::copyStream(lResult, null);
        }
    }
    catch (Poco::Exception& exc) {
        m_errors = exc.displayText();
    }
    return false;
}
//===============================================
