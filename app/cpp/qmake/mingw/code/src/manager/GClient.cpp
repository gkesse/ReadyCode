//===============================================
#include "GClient.h"
#include "GLog2.h"
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
void GClient::setMethod(const GString& _method) {
    m_method = _method;
}
//===============================================
void GClient::setApiKey(const GString& _apiKey) {
    m_apiKey = _apiKey;
}
//===============================================
void GClient::setUsername(const GString& _username) {
    m_username = _username;
}
//===============================================
void GClient::setPassword(const GString& _password) {
    m_password = _password;
}
//===============================================
void GClient::setRequest(const GString& _request) {
    m_request = _request;
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
    GLOGT(eGMSG, lData.c_str());
    GSocket2::callServer();
    GLOGI2->deserialize(m_response);
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
    m_dataOut += GFORMAT("%s;", m_method.c_str());
    m_dataOut += GFORMAT("api_key:%s|", m_apiKey.c_str());
    m_dataOut += GFORMAT("username:%s|", m_username.c_str());
    m_dataOut += GFORMAT("password:%s|", m_password.c_str());
    m_dataOut += GFORMAT("size:%d;", lSize);
    m_dataOut += GFORMAT("%s", m_request.c_str());

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
    int lCount = lHeader.countSep("|");

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
bool GClient::loadErrors() {
    m_response = m_dataIn.substr(m_headerSize);
    if(m_response == "") return false;
    return true;
}
//===============================================
