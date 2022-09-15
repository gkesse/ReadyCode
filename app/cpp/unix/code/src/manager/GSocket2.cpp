//===============================================
#include "GSocket2.h"
#include "GPath.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GThread.h"
#include "GCode.h"
#include "GString.h"
#include "GEnv.h"
#include "GHost.h"
#include "GHttp.h"
#include "GThread2.h"
//===============================================
GSocket2::GSocket2()
: GObject() {
    m_domain = 0;
    m_type = 0;
    m_protocol = 0;
    m_family = 0;
    m_port = 0;
    m_backlog = 0;
    m_server = 0;
    m_socket = 0;
}
//===============================================
GSocket2::~GSocket2() {

}
//===============================================
void GSocket2::setModule(const GString2& _module) {
    m_module = _module;
}
//===============================================
void GSocket2::setHostname(const GString2& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GSocket2::setMessage(const GString2& _message) {
    m_message = _message;
}
//===============================================
void GSocket2::setDomain(int _domain) {
    m_domain = _domain;
}
//===============================================
void GSocket2::setType(int _type) {
    m_type = _type;
}
//===============================================
void GSocket2::setProtocol(int _protocol) {
    m_protocol = _protocol;
}
//===============================================
void GSocket2::setFamily(int _family) {
    m_family = _family;
}
//===============================================
void GSocket2::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GSocket2::setBacklog(int _backlog) {
    m_backlog = _backlog;
}
//===============================================
bool GSocket2::run() {
    int lSocket = socket(m_domain, m_type, m_protocol);
    if(lSocket == -1) return false;

    struct sockaddr_in lAddressIn;
    bzero(&lAddressIn, sizeof(lAddressIn));
    lAddressIn.sin_family = m_family;
    lAddressIn.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddressIn.sin_port = htons(m_port);

    int lBind = bind(lSocket, (struct sockaddr*)&lAddressIn, sizeof(lAddressIn));
    if(lBind == -1) return false;

    int lListen = listen(lSocket, m_backlog);
    if(lListen == -1) return false;

    GLOGT(eGMSG, "%s", m_message.c_str());

    struct sockaddr_in lAddress2;
    socklen_t lSize = sizeof(lAddress2);

    GThread2 lThread;
    lThread.setThreadCB((void*)onThreadCB);

    while(1) {
        GSocket2* lClient = new GSocket2;
        int lSocket2 = accept(lSocket, (struct sockaddr*)&lAddress2, &lSize);
        if(lSocket2 == -1) return false;
        lClient->m_socket = lSocket2;
        lClient->m_server = this;
        lThread.setParams((void*)lClient);
        if(!lThread.run()) return false;
    }

    return true;
}
//===============================================
void* GSocket2::onThreadCB(void* _params) {
    GSocket2* lClient = (GSocket2*)_params;
    GSocket2* lServer = lClient->m_server;
    int lSocket = lClient->m_socket;
    GString2 lDataIn;

    if(lClient->readMethod(lSocket, lDataIn)) {
        if(lDataIn.startBy("GET")) {
            lClient->runGet(lSocket, lDataIn);
        }
    }

    close(lSocket);
    delete lClient;
    return 0;
}
//===============================================
bool GSocket2::runGet(int _socket, GString2& _data) {
    GHttp lHttp;
    lHttp.setSocket(m_socket);
    if(readHeader(_socket, _data)) {
        GLOGT(eGMSG, "[%s]", _data.c_str());
        analyzeHeader(_data, lHttp);
        lHttp.onModule();
    }
    return true;
}
//===============================================
bool GSocket2::readMethod(int _socket, GString2& _data) {
    char lBuffer[ANALYZE_SIZE + 1];
    int lBytes = recv(_socket, lBuffer, ANALYZE_SIZE, 0);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    _data += lBuffer;
    return true;
}
//===============================================
bool GSocket2::readHeader(int _socket, GString2& _data) {
    char lChar;
    int lIndex = 0;
    int lSize = 0;
    while(1) {
        int lBytes = recv(_socket, &lChar, 1, 0);
        if(lBytes <= 0) return false;
        _data += lChar;
        if(isHeader(lChar, lIndex)) return true;
        lSize++;
        if(lSize >= HEADER_SIZE) return false;
    }
    return false;
}
//===============================================
bool GSocket2::isHeader(char _char, int& _index) const {
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
bool GSocket2::analyzeHeader(const GString2& _data, GHttp& _http) {
    int lIndex = 0;
    GString2 lLine = "";
    for(int i = 0; i < _data.size(); i++) {
        char lChar = _data[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            GString2 lMethod = lLine.extract(0, " \r\n").trim();
            GString2 lUrl = lLine.extract(1, " \r\n").trim();
            GString2 lVersion = lLine.extract(2, " \r\n").trim();
            _http.setMethod(lMethod);
            _http.setUrl(lUrl);
            _http.setVersion(lVersion);
            lLine = "";
            break;
        }
    }
    for(int i = 0; i < _data.size(); i++) {
        char lChar = _data[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            if(lLine.startBy("Host")) {
                GString2 lHostname = lLine.extract(1, ":\r\n").trim();
                GString2 lPort = lLine.extract(2, ":\r\n").trim();
                _http.setHostname(lHostname);
                _http.setPort(lPort.toInt());
            }
            else if(lLine.startBy("Connection")) {
                GString2 lConnection = lLine.extract(1, ":\r\n").trim();
                _http.setConnection(lConnection);
            }
            else if(lLine.startBy("Cache-Control")) {
                GString2 lCacheControl = lLine.extract(1, ":\r\n").trim();
                _http.setCacheControl(lCacheControl);
            }
            else if(lLine.startBy("Upgrade-Insecure-Requests")) {
                GString2 lUpgradeInsecureRequests = lLine.extract(1, ":\r\n").trim();
                _http.setUpgradeInsecureRequests(lUpgradeInsecureRequests);
            }
            else if(lLine.startBy("User-Agent")) {
                GString2 lUserAgent = lLine.extract(1, ":\r\n").trim();
                _http.setUserAgent(lUserAgent);
            }
            else if(lLine.startBy("Accept")) {
                GString2 lAccept = lLine.extract(1, ":\r\n").trim();
                _http.setAccept(lAccept);
            }
            else if(lLine.startBy("Accept-Encoding")) {
                GString2 lAcceptEncoding = lLine.extract(1, ":\r\n").trim();
                _http.setAcceptEncoding(lAcceptEncoding);
            }
            else if(lLine.startBy("Accept-Language")) {
                GString2 lAcceptLanguage = lLine.extract(1, ":\r\n").trim();
                _http.setAcceptLanguage(lAcceptLanguage);
            }
            lLine = "";
        }
    }
    return true;
}
//===============================================
bool GSocket2::isLine(char _char, int& _index) const {
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
