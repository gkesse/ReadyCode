//===============================================
#include "GHttp.h"
#include "GFormat.h"
#include "GLog.h"
//===============================================
GHttp::GHttp()
: GObject() {
    m_method = "";
    m_url = "";
    m_version = "";
    m_status = "";
    m_reason = "";
    m_date = "";
    m_server = "";
    m_lastModified = "";
    m_contentType = "";
    m_contentLength = 0;
    m_connection = "";
}
//===============================================
GHttp::~GHttp() {

}
//===============================================
void GHttp::setMethod(const std::string& _method) {
    m_method = _method;
}
//===============================================
void GHttp::setUrl(const std::string& _url) {
    m_url = _url;
}
//===============================================
void GHttp::setVerion(const std::string& _version) {
    m_version = _version;
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
