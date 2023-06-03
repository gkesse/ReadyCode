//===============================================
#include "GOpenSSLTest.h"
#include "GOpenSSL.h"
//===============================================
GOpenSSLTest::GOpenSSLTest()
: GObject() {

}
//===============================================
GOpenSSLTest::~GOpenSSLTest() {

}
//===============================================
void GOpenSSLTest::run(int _argc, char** _argv) {
    GString lMethod;
    if(_argc > 2) lMethod = _argv[2];
    if(lMethod == "") {
        m_logs.addError("La méthode est obligatoire.");
    }
    else if(lMethod == "test") {
        runTest(_argc, _argv);
    }
    else {
        m_logs.addError("La méthode est inconnue.");
    }
}
//===============================================
void GOpenSSLTest::runTest(int _argc, char** _argv) {
    GOpenSSL lOpenSSL;
    lOpenSSL.setStartMessage("Démarrage du serveur...\n");
    lOpenSSL.setStopMessage("Arrêt du serveur...\n");
    lOpenSSL.setHostname("0.0.0.0");
    lOpenSSL.setPort(9081);
    lOpenSSL.setBacklog(10);
    lOpenSSL.setCountry("FR");
    lOpenSSL.setCommonName("ReadyDev");
    lOpenSSL.setPrivateKeyFile("/home/gkesse/.readydev/data/certificates/privkey.pem");
    lOpenSSL.setCertificateFile("/home/gkesse/.readydev/data/certificates/fullchain.pem");
    lOpenSSL.setHasGenerateCertificate(false);
    lOpenSSL.run();
    m_logs.addLogs(lOpenSSL.getLogs());
}
//===============================================
