//===============================================
#ifndef _GPocoServerApp_
#define _GPocoServerApp_
//===============================================
#include "GObject.h"
//===============================================
class GPocoServerApp : public Poco::Util::ServerApplication {
public:
    GPocoServerApp();
    ~GPocoServerApp();
    //
    void setModule(const GString& _module);
    void setFormat(const GString& _format);
    void setPort(int _port);
    // time
    void onMainTime(const std::vector<GString>& _args);
    void onMainEcho(const std::vector<GString>& _args);

protected:
    void initialize(Poco::Util::Application& _app);
    void uninitialize();
    int main(const std::vector<GString>& _args);

private:
    GString m_module;
    GString m_format;
    int m_port;
};
//==============================================
#endif
//==============================================
