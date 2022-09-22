//===============================================
#include "GServer.h"
#include "GLog.h"
#include "GHttp.h"
//===============================================
GServer::GServer()
: GSocket2() {
    setMethod(API_METHOD);
    setApiKey(API_KEY);
    setUsername(API_USERNAME);
    setPassword(API_PASSWORD);
}
//===============================================
GServer::~GServer() {

}
void GServer::setMethod(const GString2& _method) {
    m_method = _method;
}
//===============================================
void GServer::setApiKey(const GString2& _apiKey) {
    m_apiKey = _apiKey;
}
//===============================================
void GServer::setUsername(const GString2& _username) {
    m_username = _username;
}
//===============================================
void GServer::setPassword(const GString2& _password) {
    m_password = _password;
}
//===============================================
void GServer::setResponse(const GString2& _response) {
    m_response = _response;
}
//===============================================
void GServer::run(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    setModule("tcp");
    setHostname("0.0.0.0");
    setPort(9001);
    setDomain(AF_INET);
    setType(SOCK_STREAM);
    setProtocol(IPPROTO_TCP);
    setFamily(AF_INET);
    setBacklog(5);
    setMessage("Démarrage du serveur...");
    GSocket2::runServer();
}
//===============================================
bool GServer::onRunServerTcp() {
    if(m_dataIn.startBy(m_method)) {
        onReadyApp();
    }
    else if(m_dataIn.startBy("GET")) {
        onHttpApp();
    }
    return true;
}
//===============================================
bool GServer::onReadyApp() {
    if(!isReadyApp()) return false;
    if(!readData(m_diffSize)) return false;
    if(!readRequest()) return false;
    setResponse(m_request);
    createData();
    m_request.print();
    return true;
}
//===============================================
bool GServer::onHttpApp() {
    GHttp lHttp;
    lHttp.setClient(this);
    lHttp.runHttp();
    return true;
}
//===============================================
bool GServer::isReadyApp() {
    GString2 lHeader = m_dataIn.extract(1, ";").trim();
    GString2 lApiKey, lUsername, lPassword, lSize;
    int lCount = lHeader.count("|");

    for(int i = 0; i < lCount; i++) {
        GString2 lWord = lHeader.extract(i, "|").trim();
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
bool GServer::readRequest() {
    m_request = m_dataIn.substr(m_headerSize);
    if(m_request == "") return false;
    return true;
}
//===============================================
bool GServer::createData() {
    if(m_response == "") return false;
    if(m_method == "") return false;
    if(m_apiKey == "") return false;
    if(m_username == "") return false;
    if(m_password == "") return false;

    int lSize = m_response.size();

    m_dataOut += sformat("%s;", m_method.c_str());
    m_dataOut += sformat("api_key:%s|", m_apiKey.c_str());
    m_dataOut += sformat("username:%s|", m_username.c_str());
    m_dataOut += sformat("password:%s|", m_password.c_str());
    m_dataOut += sformat("size:%d;", lSize);
    m_dataOut += sformat("%s", m_response.c_str());
    return true;
}
//===============================================
