//===============================================
#include "GPoco.h"
#include "GPocoServerApp.h"
#include "GPocoRequestFactory.h"
#include "GPocoGetXml.h"
#include "GPocoPostXml.h"
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
    m_hasUserAgent = false;
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
    m_username          = GAPP->getData("poco", "api_username");
    m_password          = GAPP->getData("poco", "api_password");
    m_portProd          = GAPP->getData("poco", "port_prod").toInt();
    m_portTest          = GAPP->getData("poco", "port_test").toInt();
    m_port              = (m_isTestEnv ? m_portTest : m_portProd);
    m_status            = Poco::Net::HTTPResponse::HTTP_OK;

    m_privateKeyFile    = GAPP->getData("poco", "private_key_file");
    m_certificateFile   = GAPP->getData("poco", "certificate_file");
    m_cacertFile        = GAPP->getData("poco", "cacert_file");
}
//===============================================
bool GPoco::initSSL() {
    Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> lPrivateKeyPassphraseHandler = new Poco::Net::KeyConsoleHandler(false);
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> lInvalidCertificateHandler = new Poco::Net::ConsoleCertificateHandler(false);

    Poco::Net::Context::Ptr lContext = new Poco::Net::Context(
            Poco::Net::Context::TLS_SERVER_USE
            , m_privateKeyFile.c_str()
            , m_certificateFile.c_str()
            , m_cacertFile.c_str()
            , Poco::Net::Context::VERIFY_RELAXED
            , 9
            , false
            , "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
    );

    if(lContext) {
        Poco::Net::SSLManager::instance().initializeServer(lPrivateKeyPassphraseHandler, lInvalidCertificateHandler, lContext);
    }
    else {
        m_logs.addError("Erreur le context n'est pas initialisé.");
    }

    return !m_logs.hasErrors();
}
//===============================================
void GPoco::setPoco(const GPoco& _obj) {
    m_protocol = _obj.m_protocol;
    m_verb = _obj.m_verb;
    m_port = _obj.m_port;
    m_status = _obj.m_status;
    m_contentType = _obj.m_contentType;
    m_request = _obj.m_request;
    m_response = _obj.m_response;
    m_hasUserPass = _obj.m_hasUserPass;
    m_hasContentType = _obj.m_hasContentType;
    m_hasUserAgent = _obj.m_hasUserAgent;
    m_userAgent = _obj.m_userAgent;
    m_username = _obj.m_username;
    m_password = _obj.m_password;
    m_logs.addLogs(_obj.m_logs);
}
//===============================================
void GPoco::setProtocol(const GString& _protocol) {
    m_protocol = _protocol;
}
//===============================================
void GPoco::setStartMessage(const GString& _startMessage) {
    m_startMessage = _startMessage;
}
//===============================================
void GPoco::setStopMessage(const GString& _stopMessage) {
    m_stopMessage = _stopMessage;
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
void GPoco::setHasUserAgent(bool _hasUserAgent) {
    m_hasUserAgent = _hasUserAgent;
}
//===============================================
void GPoco::setUserAgent(const GString& _userAgent) {
    m_userAgent = _userAgent;
}
//===============================================
void GPoco::setUsername(const GString& _username) {
    m_username = _username;
}
//===============================================
void GPoco::setPassword(const GString& _password) {
    m_password = _password;
}
//===============================================
void GPoco::setPrivateKeyFile(const GString& _privateKeyFile) {
    m_privateKeyFile = _privateKeyFile;
}
//===============================================
void GPoco::setCertificateFile(const GString& _certificateFile) {
    m_certificateFile = _certificateFile;
}
//===============================================
void GPoco::setCacertFile(const GString& _cacertFile) {
    m_cacertFile = _cacertFile;
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
bool GPoco::onPostUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(_request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials lCredentials(_request);
        GString lUsername = lCredentials.getUsername();
        GString lPassword = lCredentials.getPassword();
        if(lUsername == m_username && lPassword == m_password) {
            if(!_request.getContentType().empty()) {
                if(_request.getContentType() == "application/xml") {
                    onPostXml(_request, _response);
                }
                else {
                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                    m_logs.addTechError("Erreur le type du contenu est inconnu.");
                }
            }
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logs.addTechError("Erreur le type du contenu est obligatoire.");
            }
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le mot de passe est incorrect.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le mot de passe est obligatoire.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onPostUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(_request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials lCredentials(_request);
        GString lUsername = lCredentials.getUsername();
        GString lPassword = lCredentials.getPassword();
        if(lUsername == m_username && lPassword == m_password) {
            onGetXml(_request, _response);
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le mot de passe est incorrect.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le mot de passe est obligatoire.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onPostNoUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(!_request.getContentType().empty()) {
        if(_request.getContentType() == "application/xml") {
            onPostXml(_request, _response);
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le type du contenu est inconnu.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le type du contenu est obligatoire.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onPostNoUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    onPostXml(_request, _response);
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onPostXml(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GPocoPostXml lPoco;
    lPoco.setPoco(*this);
    lPoco.run(_request.getURI());
    setPoco(lPoco);
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onGetUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(_request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials lCredentials(_request);
        GString lUsername = lCredentials.getUsername();
        GString lPassword = lCredentials.getPassword();
        if(lUsername == m_username && lPassword == m_password) {
            if(!_request.getContentType().empty()) {
                if(_request.getContentType() == "application/xml") {
                    onGetXml(_request, _response);
                }
                else {
                    m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                    m_logs.addTechError("Erreur le type du contenu est inconnu.");
                }
            }
            else {
                m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
                m_logs.addTechError("Erreur le type du contenu est obligatoire.");
            }
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le mot de passe est incorrect.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le mot de passe est obligatoire.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onGetUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    if(_request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials lCredentials(_request);
        GString lUsername = lCredentials.getUsername();
        GString lPassword = lCredentials.getPassword();
        if(lUsername == m_username && lPassword == m_password) {
            onGetXml(_request, _response);
        }
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("Erreur le mot de passe est incorrect.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le mot de passe est obligatoire.");
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
            m_logs.addTechError("Erreur le type du contenu est inconnu.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le type du contenu est obligatoire.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onGetNoUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    onGetXml(_request, _response);
    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onGetXml(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GPocoGetXml lPoco;
    lPoco.setPoco(*this);
    lPoco.run(_request.getURI());
    setPoco(lPoco);
    return !m_logs.hasErrors();
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
        if(lKey == "User-Agent") {
            m_userAgentData = lValue;
        }
    }

    if(_request.hasContentLength()) {
        std::istream& lInput = _request.stream();
        std::string lOutput;
        Poco::StreamCopier::copyToString(lInput, lOutput, _request.getContentLength());
        m_request = lOutput;
    }

    if(m_protocol == "") {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le protocol est obligatoire.");
    }
    // http
    else if(m_protocol == "http") {
        if(_request.getMethod() == "") {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("La méthode est obligatoire.");
        }
        // http : post
        else if(_request.getMethod() == "POST") {
            if(m_hasUserPass) {
                if(m_hasContentType) {
                    onPostUsernamePasswordContentType(_request, _response);
                }
                else {
                    onPostUsernamePasswordNoContentType(_request, _response);
                }
            }
            else {
                if(m_hasContentType) {
                    onPostNoUsernamePasswordContentType(_request, _response);
                }
                else {
                    onPostNoUsernamePasswordNoContentType(_request, _response);
                }
            }
        }
        // http : get
        else if(_request.getMethod() == "GET") {
            if(m_hasUserPass) {
                if(m_hasContentType) {
                    onGetUsernamePasswordContentType(_request, _response);
                }
                else {
                    onGetUsernamePasswordNoContentType(_request, _response);
                }
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
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("La méthode est inconnue.");
        }
    }
    // https
    else if(m_protocol == "https") {
        if(_request.getMethod() == "") {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("La méthode est obligatoire.");
        }
        // https : post
        else if(_request.getMethod() == "POST") {
            if(m_hasUserPass) {
                if(m_hasContentType) {
                    onPostUsernamePasswordContentType(_request, _response);
                }
                else {
                    onPostUsernamePasswordNoContentType(_request, _response);
                }
            }
            else {
                if(m_hasContentType) {
                    onPostNoUsernamePasswordContentType(_request, _response);
                }
                else {
                    onPostNoUsernamePasswordNoContentType(_request, _response);
                }
            }
        }
        // https : get
        else if(_request.getMethod() == "GET") {
            if(m_hasUserPass) {
                if(m_hasContentType) {
                    onGetUsernamePasswordContentType(_request, _response);
                }
                else {
                    onGetUsernamePasswordNoContentType(_request, _response);
                }
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
        else {
            m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
            m_logs.addTechError("La méthode est inconnue.");
        }
    }
    else {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        m_logs.addTechError("Erreur le protocole n'est pas géré.");
    }

    return !m_logs.hasErrors();
}
//===============================================
bool GPoco::onResponse(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GString lRequest = m_headers + m_request;

    m_responseXml.loadData(m_logs.serialize());
    if(m_userAgentData == m_userAgent || !m_hasUserAgent) {
        m_response = m_responseXml.toString();
        m_contentType = "application/xml; charset=UTF-8";
    }
    else {
        m_response = m_responseXml.toJson();
        m_contentType = "application/json; charset=UTF-8";
    }

    GLOGT(eGMSG, "[RECEPTION] : (%d)(%d)\n%s\n", lRequest.size(), (int)m_status, lRequest.c_str());
    GLOGT(eGMSG, "[EMISSION] : (%d)(%d)\n%s\n", m_response.size(), (int)m_status, m_response.c_str());

    if(m_logs.hasTechErrors()) {
        m_status = Poco::Net::HTTPResponse::HTTP_NOT_FOUND;
        GLog lLog;
        lLog.addError("Erreur lors de la connexion au serveur.");
        if(m_userAgentData == m_userAgent || !m_hasUserAgent) {
            m_response = lLog.serialize();
            m_contentType = "application/xml; charset=UTF-8";
        }
        else {
            m_response = lLog.toJson();
            m_contentType = "application/json; charset=UTF-8";
        }
    }

    if(m_contentType.isEmpty()) {
        m_contentType = "application/xml; charset=UTF-8";
    }

    _response.setVersion(Poco::Net::HTTPMessage::HTTP_1_1);
    _response.setStatus(m_status);
    _response.setContentLength(m_response.size());
    _response.setContentType(m_contentType.c_str());
    std::ostream& lStream = _response.send();
    lStream.write(m_response.c_str(), m_response.size());
    lStream.flush();

    return !m_logs.hasErrors();
}
//===============================================
