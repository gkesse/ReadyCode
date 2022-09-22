//===============================================
#include "GSocket2.h"
#include "GLog.h"
#include "GPath.h"
#include "GCode2.h"
//===============================================
GSocket2::GSocket2() {
    m_major = 0;
    m_minor = 0;
    m_domain = 0;
    m_type = 0;
    m_protocol = 0;
    m_family = 0;
    m_port = 0;
    m_socket = 0;

    setMethod(API_METHOD);
    setApiKey(API_KEY);
    setUsername(API_USERNAME);
    setPassword(API_PASSWORD);
}
//===============================================
GSocket2::~GSocket2() {

}
void GSocket2::setMajor(int _major) {
    m_major = _major;
}
//===============================================
void GSocket2::setMinor(int _minor) {
    m_minor = _minor;
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
void GSocket2::setFamily(int _family) {
    m_family = _family;
}
//===============================================
void GSocket2::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GSocket2::setHostname(const GString& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GSocket2::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
void GSocket2::setApiKey(const GString& _apiKey) {
    m_apiKey = _apiKey;
}
//===============================================
void GSocket2::setUsername(const GString& _username) {
    m_username = _username;
}
//===============================================
void GSocket2::setPassword(const GString& _password) {
    m_password = _password;
}
//===============================================
void GSocket2::setContent(const GString& _content) {
    m_content = _content;
}
//===============================================
bool GSocket2::callServer() {
    if(m_content.size() == 0) return true;
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(m_major, m_minor), &lWsaData);
    m_socket = socket(m_domain, m_type, m_protocol);
    if(m_socket == INVALID_SOCKET) return false;
    SOCKADDR_IN lAddress;
    lAddress.sin_family = m_family;
    lAddress.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    int lAnswer = connect(m_socket, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    if(lAnswer == SOCKET_ERROR) return false;

    if(createData()) {
        sendData();
    }

    closesocket(m_socket);
    WSACleanup();
    return true;
}
bool GSocket2::callServer(const GString& _data) {
    setContent(_data);
    return callServer();
}
//===============================================
GString GSocket2::callServer(const GString& _module, const GString& _method, const GString& _data) {
    GCode2 lDom;
    lDom.createDoc();
    lDom.createRequest(_module, _method);
    lDom.loadData(_data);
    GString lData = lDom.toString();
    GString lDataOut = callServer(lData);
    return lDataOut;
}
//===============================================
bool GSocket2::createData() {
    if(m_content == "") return false;
    if(m_apiKey == "") return false;
    if(m_username == "") return false;
    if(m_password == "") return false;

    int lSize = m_content.size();

    m_dataIn = "";
    m_dataIn += sformat("%s;", m_method.c_str());
    m_dataIn += sformat("api_key:%s|", m_apiKey.c_str());
    m_dataIn += sformat("username:%s|", m_username.c_str());
    m_dataIn += sformat("password:%s|", m_password.c_str());
    m_dataIn += sformat("size:%d;", lSize);
    m_dataIn += sformat("%s", m_content.c_str());

    return true;
}
//===============================================
bool GSocket2::sendData() {
    int lIndex = 0;
    int lSize = m_dataIn.size();
    const char* lBuffer = m_dataIn.c_str();

    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes <= 0) return false;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }

    return true;
}
//===============================================
