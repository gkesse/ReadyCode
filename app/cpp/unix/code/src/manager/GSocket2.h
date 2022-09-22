//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GObject.h"
//===============================================
class GSocket2 : public GObject {
public:
    GSocket2();
    ~GSocket2();

    void setModule(const GString2& _module);
    void setHostname(const GString2& _hostname);
    void setMessage(const GString2& _message);
    void setDomain(int _domain);
    void setType(int _type);
    void setProtocol(int _protocol);
    void setFamily(int _family);
    void setPort(int _port);
    void setBacklog(int _backlog);

    GString2& getDataIn();
    GString2& getDataOut();

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

    GString2 m_module;
    GString2 m_hostname;
    GString2 m_message;
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    int m_backlog;

    GString2 m_method;
    GString2 m_apiKey;
    GString2 m_username;
    GString2 m_password;
    GString2 m_content;

    int m_socket;
    GString2 m_dataIn;
    GString2 m_dataOut;
};
//==============================================
#endif
//==============================================
