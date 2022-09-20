//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GObject.h"
//===============================================
class GHttp;
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
    void setThreadCB(void* m_threadCB);

    int getSocket() const;
    GString2& getDataIn();
    const GString2& getDataIn() const;
    GString2& getDataOut();
    const GString2& getDataOut() const;

    bool readMethod();
    int readData(char* _data, int _size);
    bool readData(int _diffSize);

    int sendData(const char* _data, int _size);
    bool sendResponse();

    bool addDataIn(const GString2& _data);

    bool closeSocket();

    bool run();
    bool runHttp();

    static void* onThreadCB(void* _params);


private:
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

    int m_socket;
    GSocket2* m_server;
    GString2 m_dataIn;
    GString2 m_dataOut;
    void* m_onThreadCB;
};
//==============================================
#endif
//==============================================
