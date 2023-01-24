//===============================================
#include "GSocketReadyApp.h"
#include "GManager.h"
#include "GEnv.h"
#include "GCode.h"
#include "GApp.h"
//===============================================
GSocketReadyApp::GSocketReadyApp()
: GSocket() {
    initReadyApp();
}
//===============================================
GSocketReadyApp::~GSocketReadyApp() {

}
//===============================================
void GSocketReadyApp::setRequest(const GString& _request) {
    m_request = _request;
}
//===============================================
GString GSocketReadyApp::getRequest() const {
    return m_request;
}
//===============================================
void GSocketReadyApp::initReadyApp() {
    m_apiKeyProd    = GAPP->getData("socket", "api_key_prod");
    m_apiKeyTest    = GAPP->getData("socket", "api_key_test");
    m_apiKey        = (m_isTestEnv ? m_apiKeyTest : m_apiKeyProd);
    m_apiUsername   = GAPP->getData("socket", "api_username");
    m_apiPassword   = GAPP->getData("socket", "api_password");
}
//===============================================
bool GSocketReadyApp::runThreadCB() {
    runRequest();
    sendResponse();
    close(m_socket);
    delete this;
    return true;
}
//===============================================
bool GSocketReadyApp::runRequest() {
    if(!readData(m_dataIn, METHOD_SIZE)) return false;
    if(!isValidRequest()) return false;
    if(!readHeader()) return false;
    if(!readData(m_dataIn, m_diffSize)) return false;
    if(!readRequest()) return false;
    analyzeRequest();
    integrateErrors();
    createResponse();
    createData();
    return true;
}
//===============================================
bool GSocketReadyApp::isValidRequest() {
    if(!m_dataIn.startBy(GSocket::METHOD_RDVAPP)) return false;
    return true;
}
//===============================================
bool GSocketReadyApp::isValidRequest(const GSocketReadyApp& _obj) {
    if(_obj.m_apiKey != m_apiKey) return false;
    if(_obj.m_apiUsername  != m_apiUsername) return false;
    if(_obj.m_apiPassword  != m_apiPassword) return false;
    if(_obj.m_dataSize <= 0) return false;
    return true;
}
//===============================================
bool GSocketReadyApp::readHeader() {
    GString lHeader = m_dataIn.extract(1, ";").trim();
    GSocketReadyApp lParams;
    int lCount = lHeader.countSep("|");

    for(int i = 0; i < lCount; i++) {
        GString lWord = lHeader.extract(i, "|").trim();
        if(lWord.startBy("api_key")) {
            lParams.m_apiKey = lWord.extract(1, ":").trim();
        }
        else if(lWord.startBy("username")) {
            lParams.m_apiUsername = lWord.extract(1, ":").trim();
        }
        else if(lWord.startBy("password")) {
            lParams.m_apiPassword = lWord.extract(1, ":").trim();
        }
        else if(lWord.startBy("size")) {
            lParams.m_dataSize = lWord.extract(1, ":").trim().toInt();
        }
    }

    if(!isValidRequest(lParams)) return false;
    m_dataSize = lParams.m_dataSize;
    m_headerSize = m_dataIn.sepSize(1, ";");
    int lTotalSize = m_headerSize + m_dataSize;
    m_diffSize = lTotalSize - m_dataIn.size();
    if(m_diffSize <= 0) return false;
    return true;
}
//===============================================
bool GSocketReadyApp::readRequest() {
    m_request = m_dataIn.substr(m_headerSize);
    if(m_request == "") return false;
    return true;
}
//===============================================
bool GSocketReadyApp::analyzeRequest() {
    GManager lManager;
    lManager.setServer(this);
    lManager.onManager();
    return true;
}
//===============================================
bool GSocketReadyApp::integrateErrors() {

    return true;
}
//===============================================
bool GSocketReadyApp::createResponse() {
    if(!m_domResponse->hasCode()) return "";
    m_response = m_domResponse->toString();
    return true;
}
//===============================================
GString GSocketReadyApp::toResponse() const {
    return m_response;
}
//===============================================
bool GSocketReadyApp::addResponse(const GString& _data) {
    m_domResponse->createCode();
    m_domResponse->loadData(_data);
    return true;
}
//===============================================
bool GSocketReadyApp::createData() {
    if(m_response == "") return false;
    if(m_apiKey == "") return false;
    if(m_apiUsername == "") return false;
    if(m_apiPassword == "") return false;

    int lSize = m_response.size();

    m_dataOut += GFORMAT("%s;", GSocket::METHOD_RDVAPP);
    m_dataOut += GFORMAT("api_key:%s|", m_apiKey.c_str());
    m_dataOut += GFORMAT("username:%s|", m_apiUsername.c_str());
    m_dataOut += GFORMAT("password:%s|", m_apiPassword.c_str());
    m_dataOut += GFORMAT("size:%d;", lSize);
    m_dataOut += GFORMAT("%s", m_response.c_str());
    return true;
}
//===============================================
