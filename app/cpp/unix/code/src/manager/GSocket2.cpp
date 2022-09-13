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
    int lSocket2 = accept(lSocket, (struct sockaddr*)&lAddress2, &lSize);
    if(lSocket2 == -1) return false;

    char lBuffer[BUFFER_SIZE + 1];
    std::string lDataIn = "";
    int lBytes = recv(lSocket2, lBuffer, BUFFER_SIZE, 0);
    GLOGT(eGMSG, "[%d]", lBytes);

    while(1) {
        if(lBytes > 0) {
            lBuffer[lBytes] = 0;
            lDataIn += lBuffer;
        }
        else {
            break;
        }
        int lBytes = recv(lSocket2, lBuffer, BUFFER_SIZE, 0);
        GLOGT(eGMSG, "[%d]", lBytes);
    }

    GLOGT(eGMSG, "[%s]", lDataIn.c_str());

    return true;
}
//===============================================
