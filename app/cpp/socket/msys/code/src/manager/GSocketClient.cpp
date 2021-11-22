//===============================================
#include "GSocketClient.h"
#include "GSocket.h"
#include "GFile.h"
#include "GManager.h"
//===============================================
GSocketClient::GSocketClient() {

}
//===============================================
GSocketClient::~GSocketClient() {

}
//===============================================
void GSocketClient::run(int argc, char** argv) {
    sGApp* lApp = GResource::Instance()->getData()->app;

    GFile lFile;
    lFile.filename(lApp->cascade_file);

    GString lData;
    lData.getData(lFile.read());

    GSocket lClient;
    lClient.init();
    lClient.ip("127.0.0.1");
    lClient.address();
    lClient.createSocketTcp();
    lClient.connectToServer();
    lClient.sends(lData);
    lClient.closeSocket();
    lClient.cleanSocket();
}
//===============================================
