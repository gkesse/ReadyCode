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
    void setModule(const std::string& _key);
    void setHostname(const std::string& _hostname);
    void setFamily(int _family);
    void setPort(int _port);
    void setRepetitions(int _repetitions);
    void setFormat(const std::string& _format);
    //
    void onRunTime(int _argc, char** _argv);
    void onRunEcho(int _argc, char** _argv);
    void onRunDns(int _argc, char** _argv);
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
    std::string m_module;
    std::string m_format;
    std::string m_hostname;
    int m_port;
};
//==============================================
#endif
//==============================================
