//===============================================
#include "GPoco2.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GPoco2::GPoco2()
: GObject() {

}
//===============================================
GPoco2::~GPoco2() {

}
//===============================================
void GPoco2::setUri(const GString2& _uri) {
    m_uri = _uri;
}
//===============================================
Poco::Net::HTTPResponse& GPoco2::getHttpHeader() {
    return m_header;
}
//===============================================
GString2 GPoco2::getHttpResponse() const {
    return m_content;
}
//===============================================
bool GPoco2::getHttp() {
    try {
        Poco::URI lUri(m_uri.c_str());
        GString2 lPath(lUri.getPathAndQuery());
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
        std::cerr << exc.displayText() << std::endl;
    }
    return false;
}
//===============================================
