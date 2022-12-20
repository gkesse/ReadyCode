//===============================================
#include "GSocketTest.h"
#include "GSocket.h"
#include "GCode.h"
#include "GLog.h"
//===============================================
GSocketTest::GSocketTest(const GString& _code)
: GObject(_code) {

}
//===============================================
GSocketTest::~GSocketTest() {

}
//===============================================
void GSocketTest::run(int _argc, char** _argv) {
    GString lKey;
    if(_argc > 3) lKey = _argv[3];
    if(lKey == "client/tcp/echo") {
        runClientTcpEcho(_argc, _argv);
    }
    else {
        runDefault(_argc, _argv);
    }
}
//===============================================
void GSocketTest::runDefault(int _argc, char** _argv) {
    GLOGT(eGFUN, "Le process est inconnu.");
}
//===============================================
void GSocketTest::runClientTcpEcho(int _argc, char** _argv) {
    GLOGT(eGFUN, "");
    GSocket lSocket;
    lSocket.setModule(GSocket::SOCKET_CLIENT_TCP);
    lSocket.setProtocol(GSocket::PROTOCOL_ECHO);
    GString lResponse;
    GString lRequest = ""
            "Sous HTTP 1.0, les connexions doivent toujours etre "
            "fermees par le serveur apres l'envoi de la reponse. [1]"
            "Depuis fin 1996, les developpeurs de produits populaires "
            "(navigateurs, serveurs web, etc.) utilisant HTTP/1.0, ont "
            "commence a ajouter une extension non officielle (au protocole) nommee "
            "keep-alive afin de permettre la reutilisation d'une connexion "
            "pour plusieurs demandes/reponses. [2] [3]"
            "Si le client prend en charge le keep-alive, "
            "il ajoute un en-tete supplementaire a la requete"
            "";
    lSocket.callServer(lRequest, lResponse);
}
//===============================================
