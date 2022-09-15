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
void GHttp::setUrl(const std::string& _url) {
    m_url = _url;
}
//===============================================
void GHttp::setVersion(const std::string& _version) {
    m_version = _version;
}
//===============================================
void GHttp::setHostname(const std::string& _hostname) {
    m_hostname =_hostname;
}
//===============================================
void GHttp::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GHttp::setStatus(const std::string& _status) {
    m_status = _status;
}
//===============================================
void GHttp::setReason(const std::string& _reason) {
    m_reason = _reason;
}
//===============================================
void GHttp::setContentType(const std::string& _contentType) {
    m_contentType = _contentType;
}
//===============================================
void GHttp::setContentLength(int _contentLength) {
    m_contentLength = _contentLength;
}
//===============================================
void GHttp::setCacheControl(const std::string& _cacheControl) {
    m_cacheControl = _cacheControl;
}
//===============================================
void GHttp::setUpgradeInsecureRequests(const std::string& _upgradeInsecureRequests) {
    m_upgradeInsecureRequests = _upgradeInsecureRequests;
}
//===============================================
void GHttp::setUserAgent(const std::string& _userAgent) {
    m_userAgent = _userAgent;
}
//===============================================
void GHttp::setAccept(const std::string& _accept) {
    m_accept = _accept;
}
//===============================================
void GHttp::setAcceptEncoding(const std::string& _acceptEncoding) {
    m_acceptEncoding = _acceptEncoding;
}
//===============================================
void GHttp::setAcceptLanguage(const std::string& _acceptLanguage) {
    m_acceptLanguage = _acceptLanguage;
}
//===============================================
void GHttp::setDate(const std::string& _date) {
    m_date = _date;
}
//===============================================
void GHttp::setServer(const std::string& _server) {
    m_server = _server;
}
//===============================================
void GHttp::setLastModified(const std::string& _lastModified) {
    m_lastModified = _lastModified;
}
//===============================================
void GHttp::setConnection(const std::string& _connection) {
    m_connection = _connection;
}
//===============================================
bool GHttp::getRequest(std::string& _request) {
    return false;
}
//===============================================
bool GHttp::getResponse(std::string& _response) {
    return false;
}
//===============================================
