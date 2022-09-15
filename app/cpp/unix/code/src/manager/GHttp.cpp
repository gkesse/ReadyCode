//===============================================
#include "GHttp.h"
#include "GFormat.h"
#include "GLog.h"
//===============================================
GHttp::GHttp()
: GObject() {
    m_contentLength = 0;
    m_port = 0;
}
//===============================================
GHttp::~GHttp() {

}
//===============================================
void GHttp::setMethod(const GString2& _method) {
    m_method = _method;
}
//===============================================
void GHttp::setUrl(const GString2& _url) {
    m_url = _url;
}
//===============================================
GString2 GHttp::getUrl() const {
    return m_url;
}
//===============================================
void GHttp::setVersion(const GString2& _version) {
    m_version = _version;
}
//===============================================
void GHttp::setHostname(const GString2& _hostname) {
    m_hostname =_hostname;
}
//===============================================
void GHttp::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GHttp::setStatus(const GString2& _status) {
    m_status = _status;
}
//===============================================
void GHttp::setReason(const GString2& _reason) {
    m_reason = _reason;
}
//===============================================
void GHttp::setContentType(const GString2& _contentType) {
    m_contentType = _contentType;
}
//===============================================
void GHttp::setContentLength(int _contentLength) {
    m_contentLength = _contentLength;
}
//===============================================
void GHttp::setCacheControl(const GString2& _cacheControl) {
    m_cacheControl = _cacheControl;
}
//===============================================
void GHttp::setUpgradeInsecureRequests(const GString2& _upgradeInsecureRequests) {
    m_upgradeInsecureRequests = _upgradeInsecureRequests;
}
//===============================================
void GHttp::setUserAgent(const GString2& _userAgent) {
    m_userAgent = _userAgent;
}
//===============================================
void GHttp::setAccept(const GString2& _accept) {
    m_accept = _accept;
}
//===============================================
void GHttp::setAcceptEncoding(const GString2& _acceptEncoding) {
    m_acceptEncoding = _acceptEncoding;
}
//===============================================
void GHttp::setAcceptLanguage(const GString2& _acceptLanguage) {
    m_acceptLanguage = _acceptLanguage;
}
//===============================================
void GHttp::setDate(const GString2& _date) {
    m_date = _date;
}
//===============================================
void GHttp::setServer(const GString2& _server) {
    m_server = _server;
}
//===============================================
void GHttp::setLastModified(const GString2& _lastModified) {
    m_lastModified = _lastModified;
}
//===============================================
void GHttp::setConnection(const GString2& _connection) {
    m_connection = _connection;
}
//===============================================
bool GHttp::getRequest(GString2& _request) {
    return false;
}
//===============================================
bool GHttp::getResponse(GString2& _response) {
    return false;
}
//===============================================
