//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GObject.h"
//===============================================
class GSocket2 {
public:
    GSocket2();
    ~GSocket2();
    void setMajor(int _major);
    void setMinor(int _minor);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setHostname(const GString& _hostname);

    void setMethod(const GString& _method);
    void setApiKey(const GString& _apiKey);
    void setUsername(const GString& _username);
    void setPassword(const GString& _password);
    void setContent(const GString& _content);

    bool callServer();
    bool callServer(const GString& _data);
    GString callServer(const GString& _module, const GString& _method, const GString& _data);

    bool createData();
    bool sendData();

private:
    static constexpr const char* API_METHOD     = "RDVAPP";
    static constexpr const char* API_KEY        = "admin";
    static constexpr const char* API_USERNAME   = "admin";
    static constexpr const char* API_PASSWORD   = "admin";

    int m_major;
    int m_minor;
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    GString m_hostname;

    GString m_method;
    GString m_apiKey;
    GString m_username;
    GString m_password;
    GString m_content;

    GString m_dataIn;
    GString m_dataOut;
    SOCKET m_socket;
};
//==============================================
#endif
//==============================================
