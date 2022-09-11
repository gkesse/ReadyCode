//===============================================
#ifndef _GPoco_
#define _GPoco_
//===============================================
#include "GObject.h"
//===============================================
class GPocoApp;
//===============================================
class GPoco : public GObject {
public:
    GPoco();
    ~GPoco();
    //
    void setHostname(const std::string& _hostname);
    void setFamily(int _family);
    void setPort(int _port);
    void setRepetitions(int _repetitions);
    //
    void setKey(const std::string& _key);
    void init(int _argc, char** _argv);
    void run();
    void showLog(Poco::Exception& _exception);
    void startServerTcp();

private:
    GPocoApp* m_app;
    int m_port;
};
//==============================================
#endif
//==============================================
