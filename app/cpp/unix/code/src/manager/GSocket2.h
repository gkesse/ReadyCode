//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GObject2.h"
//===============================================
class GSocket2 : public GObject2 {
public:
    GSocket2();
    ~GSocket2();

    virtual GSocket2* clone() const;

    void setModule(const GString& _module);
    void setHostname(const GString& _hostname);
    void setMessage(const GString& _message);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setBacklog(int _backlog);

    GString& getDataIn();
    GString& getDataOut();

    int readData(char* _data, int _size);
    bool readData(int _diffSize);
    bool readMethod();

    int sendData(const char* _data, int _size);
    bool sendResponse();

    bool runServer();
    bool runServerTcp();

    static void* onThreadCB(void* _params);
    bool runThreadCB();
    bool runThreadTcp();

    virtual bool onRunServerTcp();

protected:
    static const int BUFFER_SIZE = 1024;
    static const int METHOD_SIZE = 1024;

    GString m_module;
    GString m_hostname;
    GString m_message;
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    int m_backlog;

    GString m_method;
    GString m_apiKey;
    GString m_username;
    GString m_password;
    GString m_content;

    int m_socket;
    GString m_dataIn;
    GString m_dataOut;
};
//==============================================
#endif
//==============================================
