//===============================================
#include "GServer.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket2.h"
//===============================================
GServer::GServer()
: GModule2() {
    setApiKey(API_KEY);
    setUsername(API_USERNAME);
    setPassword(API_PASSWORD);
}
//===============================================
GServer::~GServer() {

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
void GServer::run(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GSocket2 lSocket;
    lSocket.setModule("tcp");
    lSocket.setHostname("192.168.1.45");
    lSocket.setPort(9001);
    lSocket.setDomain(AF_INET);
    lSocket.setType(SOCK_STREAM);
    lSocket.setProtocol(IPPROTO_TCP);
    lSocket.setFamily(AF_INET);
    lSocket.setBacklog(5);
    lSocket.setMessage("Démarrage du serveur...");
    lSocket.setThreadCB((void*)onThreadCB);
    lSocket.run();
}
//===============================================
void* GServer::onThreadCB(void* _params) {
    GSocket2* lClient = (GSocket2*)_params;
    GString2& lDataIn = lClient->getDataIn();

    GServer lMaster;
    lMaster.setClient(lClient);

    if(lClient->readMethod()) {
        if(lDataIn.startBy("RDVAPP")) {
            lMaster.onReadyApp();
        }
    }

    lClient->sendResponse();
    lClient->closeSocket();
    delete lClient;
    return 0;
}
//===============================================
bool GServer::onReadyApp() {
    if(!isReadyApp()) return false;
    if(!readData()) return false;
    return true;
}
//===============================================
bool GServer::isReadyApp() {
    GString2& lDataIn = m_client->getDataIn();
    GString2 lHeader = lDataIn.extract(1, ";").trim();
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
    if(lApiKey != m_apiKey) return false;
    if(lApiKey != m_apiKey) return false;
    if(lSize.toInt(m_size)) return false;

    m_dSize = m_size - lDataIn.size();
    if(m_dSize < 0) return false;

    return true;
}
//===============================================
bool GServer::readData() {
    if(m_dSize == 0) return true;
    char lBuffer[BUFFER_SIZE + 1];
    int lIndex = 0;
    int lSize = 0;
    while(1) {
        int lBytes = m_client->readData(lBuffer, BUFFER_SIZE);
        if(lBytes <= 0) return false;
        lBuffer[lBytes] = 0;
        m_client->addDataIn(lBuffer);
        lSize += lBytes;
        if(lSize >= m_dSize) return false;
    }
    return true;
}
//===============================================
