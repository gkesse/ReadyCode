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
bool GSocket2::readMethod(int _socket, std::string& _data) {
    char lBuffer[ANALYZE_SIZE + 1];
    int lBytes = recv(_socket, lBuffer, ANALYZE_SIZE, 0);
    if(lBytes <= 0) return false;
    lBuffer[lBytes] = 0;
    _data += lBuffer;
    return true;
}
//===============================================
bool GSocket2::readHeader(int _socket, std::string& _data) {
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
bool GSocket2::analyzeHeader(const std::string& _data) {
    int lIndex = 0;
    std::string lLine = "";
    for(int i = 0; i < _data.size(); i++) {
        char lChar = _data[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            std::string lMethod = loadWord(lLine, 0, " \r\n");
            std::string lUrl = loadWord(lLine, 1, " \r\n");
            std::string lVersion = loadWord(lLine, 2, " \r\n");
            printf("[%s]\n", lMethod.c_str());
            printf("[%s]\n", lUrl.c_str());
            printf("[%s]\n", lVersion.c_str());
            lLine = "";
            break;
        }
    }
    return true;
}
//===============================================
bool GSocket2::compare(const std::string& _data1, const std::string& _data2, const std::string& _sep) {
    if(_data1.size() == 0) return false;
    if(_data2.size() == 0) return false;
    if(_data1.size() < _data2.size()) return false;
    int i = 0;
    for(; i < _data2.size(); i++) {
        if(_data1[i] != _data2[i]) return false;
    }
    for(int j = 0; j < _sep.size(); j++) {
        if(_data1[i + j] != _sep[j]) return false;
    }
    return true;
}
//===============================================
std::string GSocket2::loadWord(const std::string& _data, int _pos, const std::string& _sep) {
    std::string lWord = "";
    int lPos = 0;
    for(int i = 0; i < _data.size(); i++) {
        char lChar = _data[i];
        if(isSep(lChar, _sep)) {
            if(lPos == _pos) return lWord;
            lWord = "";
            lPos++;
        }
        lWord += lChar;
    }
    return "";
}
//===============================================
bool GSocket2::sendPageNotFound(int _socket) {
    int lBytes = send(_socket, m_notFound.c_str(), m_notFound.size(), 0);
    if(lBytes <= 0) return false;
    return true;
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
bool GSocket2::isSep(char _char, const std::string& _sep) const {
    for(int i = 0; i < _sep.size(); i++) {
        if(_char == _sep[i]) return true;
    }
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
        if(isHeader(lChar, lIndex)) return true;
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

    if(readMethod(lSocket2, lDataIn)) {
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
bool GSocket2::runGet(int _socket, std::string& _data) {
    if(readHeader(_socket, _data)) {
        analyzeHeader(_data);
    }
    return true;
}
//===============================================
