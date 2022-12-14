//===============================================
#include "GCode.h"
#include "GServer.h"
#include "GLog.h"
#include "GHttp.h"
//===============================================
GServer* GServer::m_instance = 0;
//===============================================
GServer::GServer()
: GSocket() {
    createDoms();
}
//===============================================
GServer::~GServer() {

}
//===============================================
GSocket* GServer::clone() const {
    return new GServer;
}
//===============================================
GServer* GServer::Instance() {
    if(m_instance == 0) {
        m_instance = new GServer;
    }
    return m_instance;
}
//===============================================
bool GServer::createDoms() {
    m_domResponse.reset(new GCode);
    m_domResponse->createDoc();
    return true;
}
//===============================================
void GServer::setResponse(const GString& _response) {
    m_response = _response;
}
//===============================================
void GServer::setRequest(const GString& _request) {
    m_request = _request;
}
//===============================================
GString GServer::getRequest() const {
    return m_request;
}
//===============================================
GString GServer::toResponse() const {
    return m_domResponse->toString();
}
//===============================================
void GServer::run(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    runServer();
}
//===============================================
bool GServer::onRunServerTcp() {
    if(m_dataIn.startBy(m_apiMethod)) {
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
    analyzeRequest();
    integrateErrors();
    createResponse();
    createData();
    return true;
}
//===============================================
bool GServer::onHttpApp() {
    GHttp lHttp;
    lHttp.setServer(this);
    lHttp.runHttp();
    return true;
}
//===============================================
bool GServer::isReadyApp() {
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
    if(lUsername != m_apiUsername) return false;
    if(lPassword != m_apiPassword) return false;
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
bool GServer::analyzeRequest() {
    GManager lManager;
    lManager.setServer(this);
    lManager.onManager();
    return true;
}
//===============================================
bool GServer::integrateErrors() {
    addResponse(GLOGI->serialize());
    GLOGI->clearMaps();
    return true;
}
//===============================================
bool GServer::createResponse() {
    if(!m_domResponse->hasCode()) return false;
    setResponse(m_domResponse->toString());
    return true;
}
//===============================================
bool GServer::createData() {
    if(m_response == "") return false;
    if(m_apiMethod == "") return false;
    if(m_apiKey == "") return false;
    if(m_apiUsername == "") return false;
    if(m_apiPassword == "") return false;

    int lSize = m_response.size();

    m_dataOut += GFORMAT("%s;", m_apiMethod.c_str());
    m_dataOut += GFORMAT("api_key:%s|", m_apiKey.c_str());
    m_dataOut += GFORMAT("username:%s|", m_apiUsername.c_str());
    m_dataOut += GFORMAT("password:%s|", m_apiPassword.c_str());
    m_dataOut += GFORMAT("size:%d;", lSize);
    m_dataOut += GFORMAT("%s", m_response.c_str());
    return true;
}
//===============================================
bool GServer::addResponse(const GString& _data) {
    m_domResponse->createCode();
    m_domResponse->loadData(_data);
    return true;
}
//===============================================
