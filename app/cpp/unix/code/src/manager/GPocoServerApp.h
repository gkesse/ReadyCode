//===============================================
#ifndef _GPocoServerApp_
#define _GPocoServerApp_
//===============================================
#include "GInclude.h"
//===============================================
class GPocoServerApp : public Poco::Util::ServerApplication {
public:
    GPocoServerApp();
    ~GPocoServerApp();
    //
    void setModule(const std::string& _module);
    void setFormat(const std::string& _format);
    void setPort(int _port);
    // time
    void onMainTime(const std::vector<std::string>& _args);

protected:
    void initialize(Poco::Util::Application& _app);
    void uninitialize();
    int main(const std::vector<std::string>& _args);

private:
    std::string m_module;
    std::string m_format;
    int m_port;
};
//==============================================
#endif
//==============================================
