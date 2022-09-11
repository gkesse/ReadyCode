//===============================================
#ifndef _GPocoApp_
#define _GPocoApp_
//===============================================
#include "GInclude.h"
//===============================================
class GPocoApp : public Poco::Util::Application {
public:
    GPocoApp();
    ~GPocoApp();
    //
    void setKey(const std::string& _key);
    void setHostname(const std::string& _hostname);
    void setFamily(int _family);
    void setRepetition(int _repetition);
    // ping
    void onInitPing(Poco::Util::Application& _app);
    void onUninitPing();
    void onMainPing();
    void onBeginPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);
    void onReplyPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);
    void onErrorPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);
    void onEndPing(const void* _sender, Poco::Net::ICMPEventArgs& _args);

protected:
    void initialize(Poco::Util::Application& _app);
    void uninitialize();
    int main(const std::vector<std::string>& _args);

private:
    std::string m_key;
    std::string m_hostname;
    int m_family;
    int m_repetition;
    //
    Poco::Net::ICMPClient* m_icmpClient;
};
//==============================================
#endif
//==============================================
