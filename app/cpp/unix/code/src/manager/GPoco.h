//===============================================
#ifndef _GPoco_
#define _GPoco_
//===============================================
#include "GObject.h"
//===============================================
class GCode;
//===============================================
class GPoco : public GObject {
public:
    GPoco();
    ~GPoco();

public:
    void initModule();
    void cleanModule();

    void initPoco();
    bool initSSL();

    void setPoco(const GPoco& _obj);
    void setProtocol(const GString& _protocol);
    void setStartMessage(const GString& _startMessage);
    void setStopMessage(const GString& _stopMessage);
    void setVerb(const GString& _verb);
    void setPort(int _port);
    void setHasUserPass(bool _hasUserPass);
    void setHasContentType(bool _hasContentType);
    void setHasUserAgent(bool _hasUserAgent);
    void setUserAgent(const GString& _userAgent);
    void setUsername(const GString& _username);
    void setPassword(const GString& _password);
    void setPrivateKeyFile(const GString& _privateKeyFile);
    void setCertificateFile(const GString& _certificateFile);
    void setCacertFile(const GString& _cacertFile);

    int getPort() const;
    GString getProtocol() const;
    GString getStartMessage() const;
    GString getStopMessage() const;

    bool run(int _argc, char** _argv);
    bool onRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onResponse(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

private:
    bool onPostUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onPostUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onPostNoUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onPostNoUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onPostXml(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

    bool onGetUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onGetUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onGetNoUsernamePasswordContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onGetNoUsernamePasswordNoContentType(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);
    bool onGetXml(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response);

protected:
    GString m_protocol;
    GString m_verb;
    bool m_hasUserPass;
    bool m_hasContentType;
    bool m_hasUserAgent;

    bool m_isTestEnv;

    GString m_username;
    GString m_password;
    GString m_contentType;

    GString m_headers;
    GString m_request;
    GString m_response;
    GString m_userAgent;
    GString m_userAgentData;

    GString m_startMessage;
    GString m_stopMessage;

    GString m_privateKeyFile;
    GString m_certificateFile;
    GString m_cacertFile;

    int m_port;
    int m_portProd;
    int m_portTest;
    Poco::Net::HTTPResponse::HTTPStatus m_status;
};
//==============================================
#endif
//==============================================
