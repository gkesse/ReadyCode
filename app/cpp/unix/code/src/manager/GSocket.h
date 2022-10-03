//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    ~GSocket();

    virtual GSocket* clone() const;

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
    int m_domain;
    int m_type;
    int m_protocol;
    int m_family;
    int m_port;
    int m_backlog;

    GString m_startMessage;

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
