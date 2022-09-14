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
//===============================================
GSocket2::GSocket2()
: GObject() {
    m_module = "";
    m_hostname = "";
    m_message = "";
    m_domain = 0;
    m_type = 0;
    m_protocol = 0;
    m_family = 0;
    m_port = 0;
    m_backlog = 0;
}
//===============================================
GSocket2::~GSocket2() {

}
//===============================================
void GSocket2::setModule(const std::string& _module) {
    m_module = _module;
}
//===============================================
void GSocket2::setHostname(const std::string& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GSocket2::setMessage(const std::string& _message) {
    m_message = _message;
}
//===============================================
void GSocket2::setNotFound(const std::string& _notFound) {
    m_notFound = _notFound;
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
bool GSocket2::analyze(int _socket, std::string& _data) {
    char lBuffer[ANALYZE_SIZE + 1];
    int lBytes = recv(_socket, lBuffer, ANALYZE_SIZE, 0);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    _data += lBuffer;
    if(lBytes == ANALYZE_SIZE) return true;
    return false;
}
//===============================================
bool GSocket2::compare(const std::string& _data1, const std::string& _data2) {
    if(_data1.size() == 0) return false;
    if(_data2.size() == 0) return false;
    for(int i = 0; i < _data2.size(); i++) {
        if(_data1[i] != _data2[i]) return false;
    }
    return true;
}
//===============================================
bool GSocket2::sendPageNotFound(int _socket) {
    int lBytes = send(_socket, m_notFound.c_str(), m_notFound.size(), 0);
    if(lBytes <= 0) return false;
    return true;
}
//===============================================
    bool GSocket2::isGet(int _char, int& _index) const {
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
bool GSocket2::readData(int _socket, std::string& _data, int _max) {
    char lChar;
    int lIndex = 0;
    int lSize = 0;
    while(1) {
        int lBytes = recv(_socket, &lChar, 1, 0);
        if(lBytes <= 0) return false;
        lSize += lBytes;
        if(_max > 0) {if(lSize >= _max) return false;}
        _data += lChar;
        if(isGet(lChar, lIndex)) return true;
    }
    return false;
}
//===============================================
bool GSocket2::getMethod(const std::string& _data, std::string& _method) {
    if(_data.size() == 0) return false;
    int lPos = 0;
    while(1) {
        char lChar = _data[lPos++];
        if(lChar == '\0') return false;
        if(lChar == '\r') return false;
        if(lChar == '\n') return false;
        if(lChar == ' ') return true;
        _method += lChar;
    }
    return false;
}
//===============================================
bool GSocket2::getUrl(const std::string& _data, std::string& _url) {
    if(_data.size() == 0) return false;
    int lPos = 0;
    int lIndex = 0;
    while(1) {
        char lChar = _data[lPos++];
        if(lChar == '\0') return false;
        if(lChar == '\r') return false;
        if(lChar == '\n') return false;
        if(lIndex == 0) {
            if(lChar == ' ') lIndex++;
        }
        else if(lIndex == 1) {
            if(lChar == ' ') return true;
            _url += lChar;
        }
    }
    return false;
}
//===============================================
bool GSocket2::getProtocol(const std::string& _data, std::string& _protocol) {
    if(_data.size() == 0) return false;
    int lPos = 0;
    int lIndex = 0;
    while(1) {
        char lChar = _data[lPos++];
        if(lChar == '\0') return false;
        if(lIndex == 0) {
            if(lChar == ' ') lIndex++;
        }
        else if(lIndex == 1) {
            if(lChar == ' ') lIndex++;
        }
        else if(lIndex == 2) {
            if(lChar == '\r') return true;
            if(lChar == '\n') return true;
            _protocol += lChar;
        }
    }
    return false;
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
    int lSocket2 = accept(lSocket, (struct sockaddr*)&lAddress2, &lSize);
    if(lSocket2 == -1) return false;

    std::string lDataIn = "";

    if(analyze(lSocket2, lDataIn)) {
        if(compare(lDataIn, "GET")) {
            runGet(lSocket2, lDataIn);
        }
        else {sendPageNotFound(lSocket2);}
    }
    else {sendPageNotFound(lSocket2);}


    GLOGT(eGMSG, "[%s]\n", lDataIn.c_str());

    return true;
}
//===============================================
bool GSocket2::runGet(int _socket, const std::string& _data) {
    std::string lDataOut = ""
            "HTTP/1.0 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<html><head><title>My 1st Web Server</title></head>"
            "<body><h1>Hello, world!</h1></body></html>";
    int lBytes = send(_socket, lDataOut.c_str(), lDataOut.size(), 0);
    if(lBytes <= 0) return false;
    return true;
}
//===============================================
