//===============================================
#include "GClient.h"
#include "GLog.h"
#include "GCode.h"
//===============================================
GClient* GClient::m_instance = 0;
//===============================================
GClient::GClient()
: GSocket() {
    m_dataSize = 0;
    m_diffSize = 0;
    m_headerSize = 0;
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
void GClient::setRequest(const GString& _request) {
    m_request = _request;
}
//===============================================
GString GClient::callServer(const GString& _module, const GString& _method, const GString& _data) {
    GCode lDom;
    lDom.createDoc();
    lDom.createRequest(_module, _method);
    lDom.loadData(_data);
    GString lData = lDom.toString();
    setRequest(lData);
    GLOGT(eGOFF, lData.c_str());
    //GSocket::callServer();
    GLOGI->deserialize(m_response);
    GLOGT(eGOFF, m_response.c_str());
    return m_response;
}
//===============================================
bool GClient::createData() {
    if(m_request == "") return false;
    if(m_apiMethod == "") return false;
    if(m_apiKey == "") return false;
    if(m_apiUsername == "") return false;
    if(m_apiPassword == "") return false;

    int lSize = m_request.size();

    m_dataOut = "";
    m_dataOut += GFORMAT("%s;", m_apiMethod.c_str());
    m_dataOut += GFORMAT("api_key:%s|", m_apiKey.c_str());
    m_dataOut += GFORMAT("username:%s|", m_apiUsername.c_str());
    m_dataOut += GFORMAT("password:%s|", m_apiPassword.c_str());
    m_dataOut += GFORMAT("size:%d;", lSize);
    m_dataOut += GFORMAT("%s", m_request.c_str());

    return true;
}
//===============================================
bool GClient::onCallServer() {
    if(m_dataIn.startBy(m_apiMethod)) {
        onReadyApp();
    }
    return true;
}
//===============================================
bool GClient::onReadyApp() {
    if(!isReadyApp()) return false;
    if(!readData(m_dataOut, m_diffSize)) return false;
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
