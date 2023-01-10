//===============================================
#include "GPoco.h"
#include "GPocoServerApp.h"
#include "GPocoRequestFactory.h"
#include "GPocoGetXml.h"
#include "GEnv.h"
#include "GManager.h"
#include "GCode.h"
#include "GApp.h"
//===============================================
GPoco::GPoco()
: GObject() {
    m_isTestEnv = false;
    m_status = Poco::Net::HTTPResponse::HTTP_OK;
    m_portTest = 0;
    m_portProd = 0;
    m_port = 0;
    m_hasUserPass = false;
    m_hasContentType = false;
}
//===============================================
GPoco::~GPoco() {

}
//===============================================
void GPoco::initModule() {
    Poco::Net::initializeSSL();
}
//===============================================
void GPoco::cleanModule() {
    Poco::Net::uninitializeSSL();
}
//===============================================
void GPoco::initPoco() {
    GEnv lEnv;
    m_isTestEnv         = lEnv.isTestEnv();

    m_startMessage      = GAPP->getData("poco", "start_message");
    m_stopMessage       = GAPP->getData("poco", "stop_message");
    m_charset           = GAPP->getData("poco", "charset");
    m_apiUsername       = GAPP->getData("poco", "api_username");
    m_apiPassword       = GAPP->getData("poco", "api_password");
    m_portProd          = GAPP->getData("poco", "port_prod").toInt();
    m_portTest          = GAPP->getData("poco", "port_test").toInt();
    m_port              = (m_isTestEnv ? m_portTest : m_portProd);
    m_status            = Poco::Net::HTTPResponse::HTTP_OK;

    m_privateKeyFile    = GAPP->getData("poco", "private_key_file");
    m_certificateFile   = GAPP->getData("poco", "certificate_file");
    m_cacertFile        = GAPP->getData("poco", "cacert_file");
}
//===============================================
bool GPoco::onHttpPostUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    // http : post : username password
    if(_request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials lCredentials(_request);
        GString lUsername = lCredentials.getUsername();
        GString lPassword = lCredentials.getPassword();
        bool lUserPassOn = (lUsername == m_apiUsername) && (lPassword == m_apiPassword);
        // http : post : username password
        if(lUserPassOn) {
            // http : post : username password : content
            if(_request.hasContentLength() && _request.getContentLength() != 0) {
                std::istream& lInput = _request.stream();
                std::string lRequest;
                Poco::StreamCopier::copyToString(lInput, lRequest, _request.getContentLength());
                m_request = lRequest;

                // http : post : username password : /readydev/com/v1
                if(_request.getURI() == "/readydev/com/v1") {
                    // http : post : username password : /readydev/com/v1 : type
                    if(!_request.getContentType().empty()) {
                        // http : post : username password : /readydev/com/v1 : application/xml
                        if(_request.getContentType() == "application/xml") {
                            GXml lXml;
                            // http : post : username password : /readydev/com/v1 : application/xml
                            if(lXml.loadXml(m_request)) {
                                GManager lManager;
                                lManager.deserialize(m_request);
                                // http : post : username password : /readydev/com/v1 : application/xml : request
                                if(lManager.isValid()) {
                                    m_logs.addLog("La requête a bien été exécutée.");
                                }
                                // http : post : username password : /readydev/com/v1 : application/xml : unknown request
                                else {
                                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                                    m_logsTech.addError("Erreur le format de la requête est incorrect.");
                                }
                            }
                            // http : post : username password : /readydev/com/v1 : unknown type
                            else {
                                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                                m_logsTech.addError("Erreur le format de la requête est invalide.");
                            }
                        }
                        // http : post : username password : /readydev/com/v1 : unknown type
                        else {
                            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                            m_logsTech.addError("Erreur le type du contenu n'est pas géré.");
                        }
                    }
                    // http : post : username password : /readydev/com/v1 : no type
                    else {
                        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                        m_logsTech.addError("Erreur le type du contenu est obligatoire.");
                    }
                }
                // http : post : username password : content : unknown verb
                else {
                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                    m_logsTech.addError("Erreur le verbe n'est pas géré.");
                }
            }
            // http : post : username password : no content
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logsTech.addError("Erreur le contenu de la requête est obligatoire");
            }
        }
        // http : post : unknown username password
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur les identifiants sont incorrects.");
        }
    }
    // http : post : no username password
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur les identifiants sont obligatoires.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpPostNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    // http : post : no username password : content
    if(_request.hasContentLength() && _request.getContentLength() != 0) {
        std::istream& lInput = _request.stream();
        std::string lRequest;
        Poco::StreamCopier::copyToString(lInput, lRequest, _request.getContentLength());
        m_request = lRequest;

        // http : post : no username password : /readydev/com/v1
        if(_request.getURI() == "/readydev/com/v1") {
            // http : post : no username password : /readydev/com/v1 : type
            if(!_request.getContentType().empty()) {
                // http : post : no username password : /readydev/com/v1 : application/xml
                if(_request.getContentType() == "application/xml") {
                    GXml lXml;
                    // http : post : no username password : /readydev/com/v1 : application/xml
                    if(lXml.loadXml(m_request)) {
                        GManager lManager;
                        lManager.deserialize(m_request);
                        // http : post : no username password : /readydev/com/v1 : application/xml : request
                        if(lManager.isValid()) {
                            m_logs.addLog("La requête a bien été exécutée.");
                        }
                        // http : post : no username password : /readydev/com/v1 : application/xml : unknown request
                        else {
                            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                            m_logsTech.addError("Erreur le format de la requête est incorrect.");
                        }
                    }
                    // http : post : no username password : /readydev/com/v1 : unknown type
                    else {
                        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                        m_logsTech.addError("Erreur le format de la requête est invalide.");
                    }
                }
                // http : post : no username password : /readydev/com/v1 : unknown type
                else {
                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                    m_logsTech.addError("Erreur le type du contenu n'est pas géré.");
                }
            }
            // http : post : no username password : /readydev/com/v1 : no type
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logsTech.addError("Erreur le type du contenu est obligatoire.");
            }
        }
        // http : post : no username password : content : unknown verb
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur le verbe n'est pas géré.");
        }
    }
    // http : post : no username password : no content
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur le contenu de la requête est obligatoire");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpGetUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    // http : get : username password
    if(_request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials lCredentials(_request);
        GString lUsername = lCredentials.getUsername();
        GString lPassword = lCredentials.getPassword();
        bool lUserPassOk = (lUsername == m_apiUsername) && (lPassword == m_apiPassword);
        if(lUserPassOk) {
            if(!_request.getContentType().empty()) {
                // http : get : username password : application/xml
                if(_request.getContentType() == "application/xml") {
                    // http : get : username password : application/xml : /readydev/api/v1
                    if(_request.getURI() == "/readydev/api/v1") {
                        m_logs.addLog("La requête a bien été exécutée.");
                    }
                    // http : get : username password : application/xml : unknown verb
                    else {
                        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                        m_logsTech.addError("Erreur le verbe n'est pas géré.");
                    }
                }
                // http : get : username password : unknown type
                else {
                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                    m_logsTech.addError("Erreur le type du contenu n'est pas géré.");
                }
            }
            // http : get : username password : no type
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logsTech.addError("Erreur le type du contenu est obligatoire.");
            }
        }
        // http : get : unknown username password
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur les identifiants sont incorrects.");
        }
    }
    // http : get : no username password
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur les identifiants sont obligatoires.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onGetNoUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(!_request.getContentType().empty()) {
        if(_request.getContentType() == "application/xml") {
            onGetXml(_request, _response);
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur le type du contenu est inconnu.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur le type du contenu est obligatoire.");
    }
    return !m_logsTech.hasErrors();
}
//===============================================
bool GPoco::onGetNoUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    onGetXml(_request, _response);
    return !m_logsTech.hasErrors();
}
//===============================================
bool GPoco::onGetXml(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GPocoGetXml lPoco;
    lPoco.run(_request.getURI());
    m_logs.addLogs(lPoco.getLogs());
    m_responseXml.loadData(lPoco.getResponse());
    m_responseXml.loadData(m_logs.serialize());
    m_response = m_responseXml.toString();
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpsPostCertificateUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpsPostCertificateNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpsGetCertificateUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpsGetCertificateNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpsGetNoCertificateUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onHttpsGetNoCertificateNoUsernamePassword(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::initSSL() {
    Poco::Net::Context::Ptr lContext = new Poco::Net::Context(
            Poco::Net::Context::SERVER_USE
            , m_privateKeyFile.c_str()
            , m_certificateFile.c_str()
            , ""
            , Poco::Net::Context::VERIFY_RELAXED
            , 9
            , false
            , "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
    );

    if(lContext) {
        Poco::Net::SSLManager::instance().initializeServer(0, 0, lContext);
    }
    else {
        m_logs.addError("Erreur le context n'est pas initialisé.");
    }

    return !m_logs.hasErrors();
}
//===============================================
void GPoco::setPoco(const GPoco& _poco) {
    m_protocol = _poco.m_protocol;
    m_verb = _poco.m_verb;
    m_port = _poco.m_port;
    m_hasUserPass = _poco.m_hasUserPass;
    m_hasContentType = _poco.m_hasContentType;
}
//===============================================
void GPoco::setProtocol(const GString& _protocol) {
    m_protocol = _protocol;
}
//===============================================
void GPoco::setVerb(const GString& _verb) {
    m_verb = _verb;
}
//===============================================
void GPoco::setPort(int _port) {
    m_port = _port;
}
//===============================================
void GPoco::setHasUserPass(bool _hasUserPass) {
    m_hasUserPass = _hasUserPass;
}
//===============================================
void GPoco::setHasContentType(bool _hasContentType) {
    m_hasContentType = _hasContentType;
}
//===============================================
int GPoco::getPort() const {
    return m_port;
}
//===============================================
GString GPoco::getProtocol() const {
    return m_protocol;
}
//===============================================
GString GPoco::getStartMessage() const {
    return m_startMessage;
}
//===============================================
GString GPoco::getStopMessage() const {
    return m_stopMessage;
}
//===============================================
bool GPoco::run(int _argc, char** _argv) {
    GPocoServerApp lServerApp(this);
    lServerApp.run(_argc, _argv);
    m_logs.addLogs(lServerApp.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GString lHost = _request.getHost();
    GString lMethod = _request.getMethod();
    GString lUri = _request.getURI();
    GString lVersion = _request.getVersion();

    m_headers += GFORMAT("%s %s %s\n", lMethod.c_str(), lUri.c_str(), lVersion.c_str());

    Poco::Net::HTTPServerRequest::ConstIterator it = _request.begin();
    for(; it != _request.end(); it++) {
        GString lKey = it->first;
        GString lValue = it->second;
        m_headers += GFORMAT("%s: %s\n", lKey.c_str(), lValue.c_str());
    }

    if(m_protocol == "") {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur le protocol est obligatoire.");
    }
    // http
    else if(m_protocol == "http") {
        // http : no method
        if(_request.getMethod() == "") {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur la méthode est obligatoire.");
        }
        // http : post
        else if(_request.getMethod() == "POST") {
            if(m_hasUserPass) {
                onHttpPostUsernamePassword(_request, _response);
            }
            else {
                onHttpPostNoUsernamePassword(_request, _response);
            }
        }
        // http : get
        else if(_request.getMethod() == "GET") {
            if(m_hasUserPass) {
                onHttpGetUsernamePassword(_request, _response);
            }
            else {
                if(m_hasContentType) {
                    onGetNoUsernamePasswordContentType(_request, _response);
                }
                else {
                    onGetNoUsernamePasswordNoContentType(_request, _response);
                }
            }
        }
        // unknown method
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur la méthode est inconnue.");
        }
    }
    // https
    else if(m_protocol == "https") {
        // https : no method
        if(_request.getMethod() == "") {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur la méthode est obligatoire.");
        }
        // https : post
        else if(_request.getMethod() == "POST") {
            if(m_hasUserPass) {
                onHttpsPostCertificateUsernamePassword(_request, _response);
            }
            else {
                onHttpsPostCertificateNoUsernamePassword(_request, _response);
            }
        }
        // https : get
        else if(_request.getMethod() == "GET") {
            if(m_hasUserPass) {
                onHttpsGetCertificateUsernamePassword(_request, _response);
            }
            else {
                onHttpsGetCertificateNoUsernamePassword(_request, _response);
            }
        }
        // https : unknown method
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur la méthode est inconnue.");
        }
    }
    // unknown protocol
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur le protocole n'est pas géré.");
    }

    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onResponse(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GString lRequest = m_headers + m_request;

    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s\n", lRequest.size(), lRequest.c_str());
    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s\n", m_response.size(), m_response.c_str());

    if(m_logsTech.hasErrors()) {
        m_logs.clearMap();
        m_logs.addError("Erreur lors de la connexion au serveur.");
        m_response = m_logs.serialize();
    }

    if(m_contentType.isEmpty()) {
        m_contentType = "application/xml";
    }

    _response.setStatus(m_status);
    _response.setContentLength(m_response.size());
    _response.setContentType(GFORMAT("%s; charset=%s", m_contentType.c_str(), m_charset.c_str()).c_str());
    std::ostream& lStream = _response.send();
    lStream << m_response.c_str();
    lStream.flush();

    return !m_logs.hasErrors();
}
//===============================================
