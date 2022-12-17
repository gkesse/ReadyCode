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
    m_username = "admin_user";
    m_password = "admin_pass_ko";
    m_port = 9081;
}
//===============================================
bool GPoco::initPoco(Poco::Net::HTTPServerRequest& _request) {
    GString lHost = _request.getHost();
    GString lMethod = _request.getMethod();
    GString lUri = _request.getURI();
    GString lVersion = _request.getVersion();

    GString lInfos;
    lInfos += GFORMAT("%s %s %s\n", lMethod.c_str(), lUri.c_str(), lVersion.c_str());

    Poco::Net::HTTPServerRequest::ConstIterator it = _request.begin();
    for(; it != _request.end(); it++) {
        GString lKey = it->first;
        GString lValue = it->second;
        lInfos += GFORMAT("%s: %s\n", lKey.c_str(), lValue.c_str());
    }

    if(_request.hasContentLength()) {
        std::istream& lInput = _request.stream();
        std::string lOutput;
        Poco::StreamCopier::copyToString(lInput, lOutput, _request.getContentLength());
        m_request = lOutput;
    }
    lInfos += GFORMAT("%s\n", m_request.c_str());

    if(_request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials lCredentials(_request);
        GString lUsername = lCredentials.getUsername();
        GString lPassword = lCredentials.getPassword();
        lInfos += GFORMAT("%s: %s\n", lUsername.c_str(), lPassword.c_str());

        Poco::Net::HTTPBasicCredentials lCreds(m_username.c_str(), m_password.c_str());
        lCreds.authenticate(_request);
    }
    else return false;

    GLOGT(eGMSG, "%s", lInfos.c_str());

    m_method = lMethod;
    m_uri = lUri;
    return true;
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
bool GPoco::doGet(const GString& _url, GString& _response) {
    try {
        Poco::URI lUri(_url.c_str());
        GString lPath(lUri.getPathAndQuery());
        if (lPath.isEmpty()) return false;

        Poco::Net::HTTPClientSession lSession(lUri.getHost(), lUri.getPort());
        Poco::Net::HTTPRequest lRequest(Poco::Net::HTTPRequest::HTTP_GET, lPath.c_str(), Poco::Net::HTTPMessage::HTTP_1_1);
        Poco::Net::HTTPResponse lResponse;
        Poco::Net::HTTPResponse::HTTPStatus lStatus;

        lSession.sendRequest(lRequest);
        std::istream& lStream = lSession.receiveResponse(lResponse);
        lStatus = lResponse.getStatus();

        if (lStatus == Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {
            Poco::Net::HTTPCredentials lCredentials(m_username.c_str(), m_password.c_str());
            lCredentials.authenticate(lRequest, lResponse);
            lSession.sendRequest(lRequest);
            std::istream& lStream = lSession.receiveResponse(lResponse);
            lStatus = lResponse.getStatus();
            if (lStatus != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {
                std::string lOutput;
                Poco::StreamCopier::copyToString(lStream, lOutput);
                _response = lOutput;
            }
        }
        else {
            std::string lOutput;
            Poco::StreamCopier::copyToString(lStream, lOutput);
            _response = lOutput;
        }
    }
    catch(Poco::Exception& e) {
        GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête.\n%s", e.displayText().c_str());
        return false;
    }
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
    if(initPoco(_request)) {
        if(m_method == "GET") {
            onGet(_request, _response);
        }
        else if(m_method == "POST") {
            onPost(_request, _response);
        }
    }

    if(m_response.isEmpty()) {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
    }

    _response.setStatus((Poco::Net::HTTPResponse::HTTPStatus)m_status);
    _response.setContentType(GFORMAT("%s; %s", m_contentType.c_str(), m_charset.c_str()).c_str());
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
