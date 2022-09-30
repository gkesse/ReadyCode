//===============================================
#ifndef _GPocoApp_
#define _GPocoApp_
//===============================================
#include "GObject.h"
//===============================================
class GPocoApp : public Poco::Util::Application {
public:
    GPocoApp();
    ~GPocoApp();
    //
    void setModule(const GString& _key);
    void setHostname(const GString& _hostname);
    void setFamily(int _family);
    void setRepetitions(int _repetitions);
    // ping
    void onInitPing(Poco::Util::Application& _app);
    void onUninitPing();
    void onMainPing(const std::vector<GString>& _args);
    void onBeginPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);
    void onReplyPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);
    void onErrorPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);
    void onEndPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);

protected:
    void initialize(Poco::Util::Application& _app);
    void uninitialize();
    int main(const std::vector<GString>& _args);

private:
    GString m_module;
    GString m_hostname;
    int m_family;
    int m_repetitions;
    //
    Poco::Net::ICMPClient* m_icmpClient;
};
//==============================================
#endif
//==============================================
