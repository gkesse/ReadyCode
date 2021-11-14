//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
//===============================================
GSocketClient::GSocketClient(QObject* _parent) :
GSocketUi(_parent) {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int _argc, char** _argv) {
    GSocket lServer;
    sGSocket lParams;
    std::string lData;
    lParams.address_ip = "127.0.0.1";

    lServer.call(lParams, "Bonjour tout le monde", lData);

    printf("Hostname.....: %s\n", lParams.hostname.c_str());
    printf("Data.........: %s\n", lData.c_str());
}
//===============================================
