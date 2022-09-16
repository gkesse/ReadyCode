//===============================================
#include "GServer.h"
#include "GLog.h"
#include "GFormat.h"
#include "GSocket2.h"
//===============================================
GServer::GServer()
: GModule2() {
    setApiKey(API_KEY);
}
//===============================================
GServer::~GServer() {

}
//===============================================
void GServer::setApiKey(const GString2& _apiKey) {
    m_apiKey = _apiKey;
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
    GString2& lDataOut = lClient->getDataOut();

    GServer lMaster;
    lMaster.setClient(lClient);

    if(lClient->readMethod()) {
        if(lDataIn.startBy("RDVAPP")) {
            lMaster.isReadyApp();
        }
    }

    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s", (int)lDataIn.size(), lDataIn.c_str());
    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s", (int)lDataOut.size(), lDataOut.c_str());

    if(lDataOut.size() > 0) {
        int lIndex = 0;
        int lSize = lDataOut.size();
        const char* lBuffer = lDataOut.c_str();

        while(1) {
            int lBytes = lClient->sendData(&lBuffer[lIndex], lSize - lIndex);
            if(lBytes <= 0) break;
            lIndex += lBytes;
            if(lIndex >= lSize) break;
        }
    }

    close(lClient->m_socket);
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
    GString2 lApiKey = lDataIn.extract(1, ";").trim();
    if(lApiKey != m_apiKey) return false;
    GString2 lSize = lDataIn.extract(2, ";").trim();
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
