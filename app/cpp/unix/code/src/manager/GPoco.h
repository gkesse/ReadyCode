//===============================================
#ifndef _GPoco_
#define _GPoco_
//===============================================
#include "GObject.h"
//===============================================
class GPocoApp;
class GPocoServerApp;
//===============================================
class GPoco : public GObject {
public:
    GPoco();
    ~GPoco();
    //
    void setModule(const GString& _key);
    void setHostname(const GString& _hostname);
    void setFamily(int _family);
    void setPort(int _port);
    void setRepetitions(int _repetitions);
    void setFormat(const GString& _format);
    void setRequest(const GString& _request);
    void setResponse(const GString& _response);
    //
    void onRunTime(int _argc, char** _argv);
    void onRunEcho(int _argc, char** _argv);
    void onRunDns(int _argc, char** _argv);
    void onRunStream(int _argc, char** _argv);
    void onRunStreamHttp(int _argc, char** _argv);
    //
    void init(int _argc, char** _argv);
    void run();
    void run(int _argc, char** _argv);
    void showLog(Poco::Exception& _exception);
    void startServer();
    void startServerTcp();

private:
    GPocoApp* m_app;
    GPocoServerApp* m_serverApp;
    GString m_module;
    GString m_format;
    GString m_hostname;
    GString m_request;
    GString m_response;
    int m_port;
    int m_family;
};
//==============================================
#endif
//==============================================
