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
    void setRepetition(int _repetition);
    //
    void setKey(const std::string& _key);
    void init(int _argc, char** _argv);
    void run();
    void showLogApp(Poco::Exception& _exception);

private:
    std::string m_hostname;
    //
    GPocoApp* m_app;
};
//==============================================
#endif
//==============================================
