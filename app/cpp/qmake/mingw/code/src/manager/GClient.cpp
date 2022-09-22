//===============================================
#include "GClient.h"
#include "GLog.h"
#include "GCode2.h"
//===============================================
GClient* GClient::m_instance = 0;
//===============================================
GClient::GClient()
: GSocket2() {
    setMethod(API_METHOD);
    setApiKey(API_KEY);
    setUsername(API_USERNAME);
    setPassword(API_PASSWORD);
}
//===============================================
GClient::~GClient() {

}
//===============================================
GClient* GClient::Instance() {
    if(m_instance == 0) {
        m_instance = new GClient;
    }
    return m_instance;
}
//===============================================
GString GClient::callServer(const GString& _module, const GString& _method, const GString& _data) {
    setMajor(2);
    setMinor(2);
    setDomain(AF_INET);
    setType(SOCK_STREAM);
    setProtocol(IPPROTO_TCP);
    setFamily(AF_INET);
    setHostname("192.168.1.45");
    setPort(9001);

    GCode2 lDom;
    lDom.createDoc();
    lDom.createRequest(_module, _method);
    lDom.loadData(_data);
    GString lData = lDom.toString();
    setRequest(lData);
    GSocket2::callServer();
    return m_response;
}
//===============================================
bool GClient::createData() {
    if(m_request == "") return false;
    if(m_method == "") return false;
    if(m_apiKey == "") return false;
    if(m_username == "") return false;
    if(m_password == "") return false;

    int lSize = m_request.size();

    m_dataOut = "";
    m_dataOut += sformat("%s;", m_method.c_str());
    m_dataOut += sformat("api_key:%s|", m_apiKey.c_str());
    m_dataOut += sformat("username:%s|", m_username.c_str());
    m_dataOut += sformat("password:%s|", m_password.c_str());
    m_dataOut += sformat("size:%d;", lSize);
    m_dataOut += sformat("%s", m_request.c_str());

    return true;
}
//===============================================
bool GClient::onCallServer() {
    if(m_dataIn.startBy(m_method)) {
        onReadyApp();
    }
    return true;
}
//===============================================
bool GClient::onReadyApp() {
    if(!isReadyApp()) return false;
    if(!readData(m_diffSize)) return false;
    if(!readResponse()) return false;

    return true;
}
//===============================================
bool GClient::isReadyApp() {
    GString lHeader = m_dataIn.extract(1, ";").trim();
    GString lApiKey, lUsername, lPassword, lSize;
    int lCount = lHeader.count("|");

    for(int i = 0; i < lCount; i++) {
        GString lWord = lHeader.extract(i, "|").trim();
        if(lWord.startBy("api_key")) {
            lApiKey = lWord.extract(1, ":").trim();
        }
        else if(lWord.startBy("username")) {
            lUsername = lWord.extract(1, ":").trim();
        }
        else if(lWord.startBy("password")) {
            lPassword = lWord.extract(1, ":").trim();
        }
        else if(lWord.startBy("size")) {
            lSize = lWord.extract(1, ":").trim();
        }
    }

    if(lApiKey != m_apiKey) return false;
    if(lUsername != m_username) return false;
    if(lPassword != m_password) return false;
    if(!lSize.toInt(m_dataSize)) return false;

    m_headerSize = m_dataIn.sepSize(1, ";");
    int lTotalSize = m_headerSize + m_dataSize;
    m_diffSize = lTotalSize - m_dataIn.size();
    if(m_diffSize < 0) return false;
    return true;
}
//===============================================
bool GClient::readResponse() {
    m_response = m_dataIn.substr(m_headerSize);
    if(m_response == "") return false;
    return true;
}
//===============================================