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
    m_contentType = "text/html";
    m_charset = "UTF-8";
    m_charset = "";
    m_port = 9081;
    m_status = 0;
}
//===============================================
void GPoco::initPoco(Poco::Net::HTTPServerRequest& _request) {
    m_host = _request.getHost();
    m_method = _request.getMethod();
    m_uri = _request.getURI();
    m_version = _request.getVersion();
    GFORMAT("%s %s %s", m_method.c_str(), m_uri.c_str(), m_version.c_str()).print();

    Poco::Net::HTTPServerRequest::ConstIterator it = _request.begin();
    for(; it != _request.end(); it++) {
        GString lKey = it->first;
        GString lValue = it->second;
        GFORMAT("%s: %s", lKey.c_str(), lValue.c_str()).print();
    }

    GString lContent;
    if(_request.hasContentLength()) {
        std::istream& lInput = _request.stream();
        std::string lOutput;
        Poco::StreamCopier::copyToString(lInput, lOutput, _request.getContentLength());
        lContent = lOutput;
    }
    lContent.print();

    const Poco::URI lUri(lContent.c_str());
    const Poco::URI::QueryParameters lParams = lUri.getQueryParameters();
    for(int i = 0; i < (int)lParams.size(); i++) {
        GString lKey = lParams.at(i).first;
        GString lValue = lParams.at(i).second;
        GFORMAT("%s : %s", lKey.c_str(), lValue.c_str()).print();
    }
}
//===============================================
void GPoco::setUri(const GString& _uri) {
    m_uri = _uri;
}
//===============================================
int GPoco::getPort() const {
    return m_port;
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
    initPoco(_request);

    if(m_method == "GET") {
        onGet(_request, _response);
    }
    else if(m_method == "POST") {
        onPost(_request, _response);
    }

    if(m_response.isEmpty()) {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
    }

    _response.setStatus((Poco::Net::HTTPResponse::HTTPStatus)m_status);
    _response.setContentType(GFORMAT("%s;%s", m_contentType.c_str(), m_charset.c_str()).c_str());
    std::ostream& lStream = _response.send();
    lStream << m_response.c_str();
    lStream.flush();
}
//===============================================
void GPoco::onGet(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(m_uri == "/") {
        m_status = Poco::Net::HTTPResponse::HTTP_OK;
        m_contentType = "text/html";
        m_response = "<h1>[GET] : Bonjour tout le monde</h1>";
    }
    else if(m_uri == "/hello") {
        m_status = Poco::Net::HTTPResponse::HTTP_OK;
        m_contentType = "text/html";
        m_response = "<h1>[GET] : Bonjour tout le monde</h1>";
    }
}
//===============================================
void GPoco::onPost(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(m_uri == "/") {
        m_status = Poco::Net::HTTPResponse::HTTP_OK;
        m_response = "<h1>[POST] : Bonjour tout le monde</h1>";
    }
    else if(m_uri == "/hello") {
        m_status = Poco::Net::HTTPResponse::HTTP_OK;
        m_response = "<h1>[POST] : Bonjour tout le monde</h1>";
    }
}
//===============================================
