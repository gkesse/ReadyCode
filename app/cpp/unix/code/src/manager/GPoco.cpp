//===============================================
#include "GPoco.h"
#include "GPocoServerApp.h"
#include "GPocoRequestFactory.h"
#include "GLog.h"
//===============================================
GPoco::GPoco(const GString& _code)
: GObject(_code) {
    initPoco();
}
//===============================================
GPoco::~GPoco() {

}
//===============================================
void GPoco::initPoco() {
    m_msgStarting = "Démarrage du serveur...";
    m_msgShutdown = "Arrêt du serveur...";

    m_status = 0;
}
//===============================================
void GPoco::setUri(const GString& _uri) {
    m_uri = _uri;
}
//===============================================
GString GPoco::getMsgStarting() const {
    return m_msgStarting;
}
//===============================================
GString GPoco::getMsgShutdown() const {
    return m_msgShutdown;
}
//===============================================
bool GPoco::extractCredentials() {
    if(m_uri.isEmpty()) return false;
    Poco::URI lUri(m_uri.c_str());
    std::string lUsername;
    std::string lPassword;
    Poco::Net::HTTPCredentials::extractCredentials(lUri, lUsername, lPassword);
    Poco::Net::HTTPCredentials credentials(lUsername, lPassword);
    m_username = lUsername;
    m_password = lPassword;
    if(m_username.isEmpty()) return false;
    if(m_password.isEmpty()) return false;
    return true;
}
//===============================================
bool GPoco::doGet() {
    if(m_uri.isEmpty()) return false;
    try {
        Poco::URI lUri(m_uri.c_str());
        GString lPath(lUri.getPathAndQuery());
        if (lPath.isEmpty()) lPath = "/";

        Poco::Net::HTTPClientSession lSession(lUri.getHost(), lUri.getPort());
        Poco::Net::HTTPRequest lRequest(Poco::Net::HTTPRequest::HTTP_GET, lPath.c_str(), Poco::Net::HTTPMessage::HTTP_1_1);
        Poco::Net::HTTPResponse lResponse;

        if (!doRequest(lSession, lRequest, lResponse)) {
            extractCredentials();
            Poco::Net::HTTPCredentials lCredentials(m_username.c_str(), m_password.c_str());
            lCredentials.authenticate(lRequest, lResponse);
            if (!doRequest(lSession, lRequest, lResponse)) {
                GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête.");
                return false;
            }
        }
    }
    catch(Poco::Exception& e) {
        GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête.\n%s", e.displayText().c_str());
        return false;
    }
    return true;
}
//===============================================
bool GPoco::doRequest(Poco::Net::HTTPClientSession& _session, Poco::Net::HTTPRequest& _request, Poco::Net::HTTPResponse& _response) {
    _session.sendRequest(_request);
    std::istream& lStream = _session.receiveResponse(_response);
    m_status = _response.getStatus();
    m_reason = _response.getReason();
    if (m_status != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {
        Poco::StreamCopier::copyStream(lStream, std::cout);
        return true;
    }
    else {
        Poco::NullOutputStream lNull;
        Poco::StreamCopier::copyStream(lStream, lNull);
        return false;
    }
    return true;
}
//===============================================
bool GPoco::doGet(const GString& _uri) {
    setUri(_uri);
    if(!doGet()) return false;
    return true;
}
//===============================================
bool GPoco::runServer(int _argc, char** _argv) {
    GPocoServerApp lServerApp(this);
    lServerApp.run(_argc, _argv);
    return true;
}
//===============================================
void GPoco::onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GLOGT(eGFUN, "");
    _response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    _response.setContentType("text/html");
    std::ostream& out = _response.send();
    out     << "<h1>Hello world!</h1>"
            << "<p>Host: "   << _request.getHost()   << "</p>"
            << "<p>Method: " << _request.getMethod() << "</p>"
            << "<p>URI: "    << _request.getURI()    << "</p>";
    out.flush();

    std::cout << std::endl
            << "Response sent for count=" << 1
            << " and URI=" << _request.getURI() << std::endl;
}
//===============================================
