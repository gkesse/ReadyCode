//===============================================
#include "GHttp.h"
//===============================================
const char* GHttp::HTTP_1_0 = "HTTP/1.0";
const char* GHttp::HTTP_1_1 = "HTTP/1.1";
//===============================================
GHttp::GHttp()
: GObject() {
    initHttp();
}
//===============================================
GHttp::~GHttp() {

}
//===============================================
void GHttp::initHttp() {
    setVersion("HTTP/1.1");
    setStatus(HTTP_OK);
    setContentType("text/html");
    setConnection("close");
}
//===============================================
void GHttp::initReason() {
    // 100
    if(m_status == 100) {m_reason = "Continue";}
    else if(m_status == 101) {m_reason = "Switching Protocols";}
    // 200
    else if(m_status == 200) {m_reason = "OK";}
    else if(m_status == 201) {m_reason = "Created";}
    else if(m_status == 202) {m_reason = "Accepted";}
    else if(m_status == 203) {m_reason = "Non-Authoritative Information";}
    else if(m_status == 204) {m_reason = "No Content";}
    else if(m_status == 205) {m_reason = "Reset Content";}
    else if(m_status == 206) {m_reason = "Partial Content";}
    // 300
    else if(m_status == 300) {m_reason = "Multiple Choices";}
    else if(m_status == 301) {m_reason = "Moved Permanently";}
    else if(m_status == 302) {m_reason = "Found";}
    else if(m_status == 303) {m_reason = "See Other";}
    else if(m_status == 304) {m_reason = "Not Modified";}
    else if(m_status == 305) {m_reason = "Use Proxy";}
    else if(m_status == 307) {m_reason = "Temporary Redirect";}
    // 400
    else if(m_status == 400) {m_reason = "Bad Request";}
    else if(m_status == 401) {m_reason = "Unauthorized";}
    else if(m_status == 402) {m_reason = "Payment Required";}
    else if(m_status == 403) {m_reason = "Forbidden";}
    else if(m_status == 404) {m_reason = "Not Found";}
    else if(m_status == 405) {m_reason = "Method Not Allowed";}
    else if(m_status == 406) {m_reason = "Not Acceptable";}
    else if(m_status == 407) {m_reason = "Proxy Authentication Required";}
    else if(m_status == 408) {m_reason = "Request Time-out";}
    else if(m_status == 409) {m_reason = "Conflict";}
    else if(m_status == 410) {m_reason = "Gone";}
    else if(m_status == 411) {m_reason = "Length Required";}
    else if(m_status == 412) {m_reason = "Precondition Failed";}
    else if(m_status == 413) {m_reason = "Request Entity Too Large";}
    else if(m_status == 414) {m_reason = "Request-URI Too Large";}
    else if(m_status == 415) {m_reason = "Unsupported Media Type";}
    else if(m_status == 416) {m_reason = "Requested range not satisfiable";}
    else if(m_status == 417) {m_reason = "Expectation Failed";}
    // 500
    else if(m_status == 500) {m_reason = "Internal Server Error";}
    else if(m_status == 501) {m_reason = "Not Implemented";}
    else if(m_status == 502) {m_reason = "Bad Gateway";}
    else if(m_status == 503) {m_reason = "Service Unavailable";}
    else if(m_status == 504) {m_reason = "Gateway Time-out";}
    else if(m_status == 505) {m_reason = "HTTP Version not supported";}
}
//===============================================
void GHttp::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GHttp::setVersion(const GString& _version) {
    m_version = _version;
}
//===============================================
void GHttp::setStatus(int _status) {
    m_status = _status;
    initReason();
}
//===============================================
void GHttp::setContentType(const GString& _contentType) {
    m_contentType = _contentType;
}
//===============================================
void GHttp::setContentText(const GString& _contentText) {
    m_contentText = _contentText;
}
//===============================================
void GHttp::setConnection(const GString& _connection) {
    m_connection = _connection;
}
//===============================================
GString GHttp::getResponseText() const {
    return m_responseText;
}
//===============================================
bool GHttp::run()  {
    if(m_module == "") {
        m_logs.addError("Le module est obligatoire.");
    }
    else if(m_module == "response") {
        runResponse();
    }
    else {
        m_logs.addError("Le module est inconnu.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GHttp::runResponse()  {
    if(m_version.isEmpty()) {
        m_logs.addError("Erreur la version HTTP est obligatoire.");
        return false;
    }
    if(m_status == 0) {
        m_logs.addError("Erreur le code du statut est obligatoire.");
        return false;
    }
    if(m_reason.isEmpty()) {
        m_logs.addError("Erreur la raison est obligatoire.");
        return false;
    }

    m_responseText = "";
    m_responseText += GFORMAT("%s %d %s\r\n", m_version.c_str(), m_status, m_reason.c_str());

    if(!m_connection.isEmpty()) {
        m_responseText += GFORMAT("Connection: %s\r\n", m_connection.c_str());
    }

    if(!m_contentType.isEmpty()) {
        m_responseText += GFORMAT("Content-Type: %s\r\n", m_contentType.c_str());
    }

    if(!m_contentText.isEmpty()) {
        m_responseText += GFORMAT("Content-Length: %d\r\n", m_contentText.size());
        m_responseText += GFORMAT("\r\n");
        m_responseText += GFORMAT("%s", m_contentText.c_str());
    }
    else {
        m_responseText += GFORMAT("\r\n");
    }

    return !m_logs.hasErrors();
}
//===============================================
