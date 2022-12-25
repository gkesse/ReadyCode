//===============================================
#include "GPoco.h"
#include "GPocoServerApp.h"
#include "GPocoRequestFactory.h"
#include "GEnv.h"
#include "GManager.h"
#include "GCode.h"
#include "GApp.h"
//===============================================
GPoco::GPoco(const GString& _code)
: GObject(_code) {
    initPoco();
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
    m_protocol          = "http";
    m_hasCertificate    = false;
    m_hasLogsTech       = false;

    m_isTestEnv         = GEnv().isTestEnv();

    m_startMessage      = GAPP->getData("poco", "start_message");
    m_stopMessage       = GAPP->getData("poco", "stop_message");
    m_contentType       = GAPP->getData("poco", "content_type");
    m_charset           = GAPP->getData("poco", "charset");
    m_apiUsername       = GAPP->getData("poco", "api_username");
    m_apiPassword       = GAPP->getData("poco", "api_password");
    m_portProd          = GAPP->getData("poco", "port_prod").toInt();
    m_portTest          = GAPP->getData("poco", "port_test").toInt();
    m_port              = (m_isTestEnv ? m_portTest : m_portProd);
    m_status            = Poco::Net::HTTPResponse::HTTP_OK;

    m_privateKeyFile    = GAPP->getData("poco", "private_key_file");
    m_certificateFile   = GAPP->getData("poco", "certificate_file");
}
//===============================================
bool GPoco::initSSL() {
    Poco::Net::Context::Ptr lContext = NULL;

    if(!m_hasCertificate) {
        lContext = new Poco::Net::Context(
                Poco::Net::Context::SERVER_USE
                , ""
                , ""
                , ""
                , Poco::Net::Context::VERIFY_RELAXED
                , 9
                , false
                , "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
        );
    }
    else {
        Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(
                Poco::Net::Context::SERVER_USE
                , m_privateKeyFile.c_str()
                , m_certificateFile.c_str()
                , ""
                , Poco::Net::Context::VERIFY_RELAXED
                , 9
                , false
                , "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
        );
    }

    if(lContext) {
        Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> lCertificate = new Poco::Net::AcceptCertificateHandler(true);
        Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> lPrivateKeyPassphraseHandler;
        lPrivateKeyPassphraseHandler = new Poco::Net::KeyConsoleHandler(true);
        Poco::Net::SSLManager::instance().initializeServer(lPrivateKeyPassphraseHandler, lCertificate, lContext);
    }
    else {
        m_logs.addError("Erreur le contexte doit être défini.");
    }

    return !m_logs.hasErrors();
}
//===============================================
void GPoco::setPoco(const GPoco& _poco) {
    m_contentType       = _poco.m_contentType;
    m_hasCertificate    = _poco.m_hasCertificate;
}
//===============================================
void GPoco::setPoco(GPoco* _poco) {
    setPoco(*_poco);
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
            Poco::Net::HTTPCredentials lCredentials(m_apiUsername.c_str(), m_apiPassword.c_str());
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
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    m_responseXml.reset(new GCode);
    m_responseXml->createDoc();

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

    // http
    if(m_protocol == "http") {
        // post
        if(_request.getMethod() == "POST") {
            if(!_request.getContentType().empty()) {
                m_logs.addLog("La requête a bien été exécutée.");
            }
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logsTech.addError("Erreur le type du contenu est obligatoire.");
            }
        }
        // get
        else if(_request.getMethod() == "GET") {
            if(!_request.getContentType().empty()) {
                m_contentType = _request.getContentType();
                // application/xml
                if(m_contentType == "application/xml") {
                    if(_request.getURI() == "/readydev/api/v1") {
                        m_logs.addLog("La requête a bien été exécutée.");
                    }
                    else {
                        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                        m_logsTech.addError("Erreur le verbe n'est pas géré.");
                    }
                }
                // application unknown
                else {
                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                    m_logsTech.addError("Erreur le type du contenu n'est pas géré.");
                }
            }
            // application unknown
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logsTech.addError("Erreur le type du contenu est obligatoire.");
            }
        }
        // method unknown
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur la méthode n'est pas gérée.");
        }
    }
    // https
    else if(m_protocol == "https") {
        // post
        if(_request.getMethod() == "POST") {
            if(_request.getURI() == "/readydev/com/v1") {
                if(!_request.getContentType().empty()) {
                    m_contentType = _request.getContentType();
                    if(m_contentType == "application/xml") {
                        if(_request.hasContentLength() && _request.getContentLength() != 0) {
                            std::istream& lInput = _request.stream();
                            std::string lRequest;
                            Poco::StreamCopier::copyToString(lInput, lRequest, _request.getContentLength());
                            m_request = lRequest;

                            GXml lXml;
                            if(lXml.loadXml(m_request)) {
                                GManager lManager;
                                lManager.deserialize(m_request);
                                if(lManager.isValid()) {
                                    if(_request.secure()) {
                                        m_logs.addLog("La requête a bien été exécutée.");
                                    }
                                    else {
                                        m_logsTech.addError("Erreur la communication doit être sécurisée.");
                                    }
                                }
                                else {
                                    m_logsTech.addError("Erreur le format de la requête est incorrect.");
                                }
                            }
                            else {
                                m_logsTech.addError("Erreur le format de la requête est invalide.");
                            }

                        }
                        else {
                            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                            m_logsTech.addError("Erreur le contenu de la requête est obligatoire");
                        }
                    }
                    else {
                        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                        m_logsTech.addError("Erreur le type du contenu n'est pas géré.");
                    }
                }
                else {
                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                    m_logsTech.addError("Erreur le type du contenu est obligatoire.");
                }
            }
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logsTech.addError("Erreur le verbe n'est pas géré.");
            }
        }
        // get
        else if(_request.getMethod() == "GET") {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur la méthode n'est pas prise en charge.");
        }
        // method unknown
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logsTech.addError("Erreur la méthode n'est pas prise en charge.");
        }
    }
    // protocol unknown
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logsTech.addError("Erreur le protocole n'est pas géré.");
    }

    m_logs.add(m_logsTech);
    addResponse(m_logs.serialize());

    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::addResponse(const GString& _data) {
    if(m_contentType == "application/xml") {
        m_responseXml->createCode();
        m_responseXml->loadData(_data);
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::doResponse() {
    if(m_contentType == "application/xml") {
        m_response = m_responseXml->toString();
    }
    else {
        m_response = m_logs.serialize();
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onResponse(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GString lRequest = m_headers + m_request;

    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s\n", lRequest.size(), lRequest.c_str());
    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s\n", m_response.size(), m_response.c_str());

    if(!m_hasLogsTech) {
        m_response = "";
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
