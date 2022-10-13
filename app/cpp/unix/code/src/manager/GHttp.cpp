//===============================================
#include "GHttp.h"
#include "GLog.h"
#include "GServer.h"
//===============================================
GHttp::GHttp()
: GManager() {
    m_status = 200;
    m_contentLength = 0;
    m_port = 0;
}
//===============================================
GHttp::~GHttp() {

}
//===============================================
void GHttp::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
void GHttp::setUrl(const GString& _url) {
    m_url = _url;
}
//===============================================
GString GHttp::getUrl() const {
    return m_url;
}
//===============================================
void GHttp::setVersion(const GString& _version) {
    m_version = _version;
}
//===============================================
void GHttp::setHostname(const GString& _hostname) {
    m_hostname =_hostname;
}
//===============================================
void GHttp::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GHttp::setStatus(const int _status) {
    m_status = _status;
}
//===============================================
void GHttp::setReason(const GString& _reason) {
    m_reason = _reason;
}
//===============================================
void GHttp::setContent(const GString& _content) {
    m_content = _content;
    m_contentLength = m_content.size();
}
//===============================================
void GHttp::setContentType(const GString& _contentType) {
    m_contentType = _contentType;
}
//===============================================
void GHttp::setContentLength(int _contentLength) {
    m_contentLength = _contentLength;
}
//===============================================
void GHttp::setCacheControl(const GString& _cacheControl) {
    m_cacheControl = _cacheControl;
}
//===============================================
void GHttp::setUpgradeInsecureRequests(const GString& _upgradeInsecureRequests) {
    m_upgradeInsecureRequests = _upgradeInsecureRequests;
}
//===============================================
void GHttp::setUserAgent(const GString& _userAgent) {
    m_userAgent = _userAgent;
}
//===============================================
void GHttp::setAccept(const GString& _accept) {
    m_accept = _accept;
}
//===============================================
void GHttp::setAcceptEncoding(const GString& _acceptEncoding) {
    m_acceptEncoding = _acceptEncoding;
}
//===============================================
void GHttp::setAcceptLanguage(const GString& _acceptLanguage) {
    m_acceptLanguage = _acceptLanguage;
}
//===============================================
void GHttp::setDate(const GString& _date) {
    m_date = _date;
}
//===============================================
void GHttp::setServer(const GString& _server) {
    m_servers = _server;
}
//===============================================
void GHttp::setLastModified(const GString& _lastModified) {
    m_lastModified = _lastModified;
}
//===============================================
void GHttp::setConnection(const GString& _connection) {
    m_connection = _connection;
}
//===============================================
bool GHttp::isLine(char _char, int& _index) const {
    if(_index == 0) {
        if(_char == '\r')_index++; else _index = 0;
    }
    else if(_index == 1) {
        if(_char == '\n') _index++; else _index = 0;
    }

    if(_index == 2) {_index = 0; return true;}
    return false;
}
//===============================================
bool GHttp::isHeader(char _char, int& _index) const {
    if(_index == 0) {
        if(_char == '\r')_index++; else _index = 0;
    }
    else if(_index == 1) {
        if(_char == '\n') _index++; else _index = 0;
    }
    else if(_index == 2) {
        if(_char == '\r') _index++; else _index = 0;
    }
    else if(_index == 3) {
        if(_char == '\n') _index++; else _index = 0;
    }

    if(_index == 4) return true;
    return false;
}
//===============================================
void GHttp::runHttp() {
    analyzeHeader();
    analyzeMethod();
}
//===============================================
bool GHttp::analyzeHeader() {
    int lIndex = 0;
    GString lLine = "";
    GString& lDataIn = m_server->getDataIn();

    for(int i = 0; i < lDataIn.size(); i++) {
        char lChar = lDataIn[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            GString lMethod = lLine.extract(0, " \r\n").trim();
            GString lUrl = lLine.extract(1, " \r\n").trim();
            GString lVersion = lLine.extract(2, " \r\n").trim();
            setMethod(lMethod);
            setUrl(lUrl);
            setVersion(lVersion);
            lLine = "";
            break;
        }
    }
    for(int i = 0; i < lDataIn.size(); i++) {
        char lChar = lDataIn[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            if(lLine.startBy("Host")) {
                GString lHostname = lLine.extract(1, ":\r\n").trim();
                GString lPort = lLine.extract(2, ":\r\n").trim();
                setHostname(lHostname);
                setPort(lPort.toInt());
            }
            else if(lLine.startBy("Connection")) {
                GString lConnection = lLine.extract(1, ":\r\n").trim();
                setConnection(lConnection);
            }
            else if(lLine.startBy("Cache-Control")) {
                GString lCacheControl = lLine.extract(1, ":\r\n").trim();
                setCacheControl(lCacheControl);
            }
            else if(lLine.startBy("Upgrade-Insecure-Requests")) {
                GString lUpgradeInsecureRequests = lLine.extract(1, ":\r\n").trim();
                setUpgradeInsecureRequests(lUpgradeInsecureRequests);
            }
            else if(lLine.startBy("User-Agent")) {
                GString lUserAgent = lLine.extract(1, ":\r\n").trim();
                setUserAgent(lUserAgent);
            }
            else if(lLine.startBy("Accept")) {
                GString lAccept = lLine.extract(1, ":\r\n").trim();
                setAccept(lAccept);
            }
            else if(lLine.startBy("Accept-Encoding")) {
                GString lAcceptEncoding = lLine.extract(1, ":\r\n").trim();
                setAcceptEncoding(lAcceptEncoding);
            }
            else if(lLine.startBy("Accept-Language")) {
                GString lAcceptLanguage = lLine.extract(1, ":\r\n").trim();
                setAcceptLanguage(lAcceptLanguage);
            }
            lLine = "";
        }
    }
    return true;
}
//===============================================
bool GHttp::analyzeMethod() {
    if(m_method == "GET") {
        analyzeGet();
    }
    else if(m_method == "POST") {
        analyzePost();
    }
    return true;
}
//===============================================
bool GHttp::analyzeGet() {
    if(m_url == "/") {
        onGetIndex();
    }
    return true;
}
//===============================================
bool GHttp::analyzePost() {
    return true;
}
//===============================================
void GHttp::onGetIndex() {
    setVersion("HTTP/1.1");
    setStatus(200);
    setReason("OK");
    setContentType("text/html");
    setConnection("Closed");

    GString lContent = ""
            "<html><head><title>[Echo]-ReadyDev</title></head>"
            "<body><h1>La connexion au serveur a réussi.</h1></body></html>"
            "";

    setContent(lContent);
    createGetData();
}
//===============================================
bool GHttp::createGetData() {
    if(m_version == "") return false;
    if(m_status == 0) return false;
    if(m_reason == "") return false;
    if(m_content == "") return false;
    if(m_contentType == "") return false;
    if(m_contentLength == 0) return false;

    GString& lDataOut = m_server->getDataOut();
    lDataOut += GFORMAT("%s %d %s\r\n", m_version.c_str(), m_status, m_reason.c_str());
    lDataOut += GFORMAT("Content-Type: %s\r\n", m_contentType.c_str());
    lDataOut += GFORMAT("Content-Length: %d\r\n", m_contentLength);

    if(m_connection != "") {
        lDataOut += GFORMAT("Connection: %s\r\n", m_connection.c_str());
    }

    lDataOut += GFORMAT("\r\n");
    lDataOut += GFORMAT("%s", m_content.c_str());
    return true;
}
//===============================================
