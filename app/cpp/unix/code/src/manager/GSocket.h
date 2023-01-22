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

    void setModule(const GString& _module);
    void setHostname(const GString& _hostname);
    void setPort(int _port);
    void setBacklog(int _backlog);
    void setStartMessage(const GString& _startMessage);
    void setStopMessage(const GString& _startMessage);
    int getSocket() const;
    bool createSocketX();

    GString getRequest() const {return "";}
    void setRequest(const GString& _request) {}
    void addResponse(const GString& _data) {}
    GSocket* createSocket() {return 0;};
    void createResponse() {};
    void sendResponse() {}
    void readDatas(GString& _data) {}
    void sendDatas(const GString& _data) {}
    GString m_dataIn;
    GString m_dataOut;
    static const int METHOD_SIZE = 1024;
    static const char* METHOD_HTTP_GET;
    static const char* METHOD_HTTP_POST;
    static const char* METHOD_RDVAPP;
    bool m_isTestEnv;

    bool run();
    bool runServerTcp();
    static void* onThreadCB(void* _params);
    virtual bool runThreadCB();
    void closeSocket();

    bool readData(GString& _dataOut, int _size);
    int sendData(const GString& _dataIn);

protected:
    static const int BUFFER_SIZE = 1024;

    int m_backlog;
    int m_port;
    int m_socket;

    GString m_module;
    GString m_hostname;
    GString m_startMessage;
    GString m_stopMessage;
};
//==============================================
#endif
//==============================================
