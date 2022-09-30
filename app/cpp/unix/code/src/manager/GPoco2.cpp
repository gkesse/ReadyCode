//===============================================
#include "GPoco2.h"
#include "GLog.h"
//===============================================
GPoco2::GPoco2()
: GObject() {

}
//===============================================
GPoco2::~GPoco2() {

}
//===============================================
void GPoco2::setUri(const GString& _uri) {
    m_uri = _uri;
}
//===============================================
Poco::Net::HTTPResponse& GPoco2::getHeader() {
    return m_header;
}
//===============================================
GString GPoco2::getContent() const {
    return m_content;
}
//===============================================
bool GPoco2::getHttp() {
    if(m_uri.isEmpty()) return false;
    try {
        Poco::URI lUri(m_uri.c_str());
        GString lPath(lUri.getPathAndQuery());
        if(lPath.isEmpty()) lPath = "/";
        Poco::Net::HTTPCredentials::extractCredentials(lUri, m_username.data(), m_password.data());
        Poco::Net::HTTPCredentials lCredentials(m_username.data(), m_password.data());
        Poco::Net::HTTPClientSession lSession(lUri.getHost(), lUri.getPort());
        Poco::Net::HTTPRequest lRequest(Poco::Net::HTTPRequest::HTTP_GET, lPath.data(), Poco::Net::HTTPMessage::HTTP_1_1);
        lSession.sendRequest(lRequest);
        std::istream& lResult = lSession.receiveResponse(m_header);

        if (m_header.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {
            Poco::StreamCopier::copyToString(lResult, m_content.data());
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
