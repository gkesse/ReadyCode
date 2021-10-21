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
    sGApp* lApp = GManager::Instance()->data()->app;

    GFile lFile;
    lFile.filename(lApp->text_file);

    GString lData;
    lData.data(lFile.read());

    GSocket lClient;
    lClient.ip("127.0.0.1");
    lClient.address();
    lClient.sockets();
    lClient.connects();
    lClient.sends(lData);
    lClient.closes();
}
//===============================================
