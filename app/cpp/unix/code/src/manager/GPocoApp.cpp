//===============================================
#include "GPocoApp.h"
#include "GLog.h"
//===============================================
GPocoApp::GPocoApp()
: Poco::Util::Application() {
    m_module = "";
    m_family = 0;
    m_repetitions = 0;
    m_icmpClient = 0;
}
//===============================================
GPocoApp::~GPocoApp() {
    delete m_icmpClient;
}
//===============================================
void GPocoApp::setModule(const GString& _module) {
    m_module = _module;
}
//===============================================
void GPocoApp::setHostname(const GString& _hostname) {
    m_hostname = _hostname;
}
//===============================================
void GPocoApp::setFamily(int _family) {
    m_family = _family;
}
//===============================================
void GPocoApp::setRepetitions(int _repetitions) {
    m_repetitions = _repetitions;
}
//===============================================
void GPocoApp::onInitPing(Poco::Util::Application& _app) {
    m_icmpClient = new Poco::Net::ICMPClient((Poco::Net::SocketAddress::Family)m_family);
    m_icmpClient->pingBegin += delegate(this, &GPocoApp::onBeginPing);
    m_icmpClient->pingReply += delegate(this, &GPocoApp::onReplyPing);
    m_icmpClient->pingError += delegate(this, &GPocoApp::onErrorPing);
    m_icmpClient->pingEnd   += delegate(this, &GPocoApp::onEndPing);
}
//===============================================
void GPocoApp::onUninitPing() {
    m_icmpClient->pingBegin -= delegate(this, &GPocoApp::onBeginPing);
    m_icmpClient->pingReply -= delegate(this, &GPocoApp::onReplyPing);
    m_icmpClient->pingError -= delegate(this, &GPocoApp::onErrorPing);
    m_icmpClient->pingEnd   -= delegate(this, &GPocoApp::onEndPing);
    Poco::Util::Application::uninitialize();
}
//===============================================
void GPocoApp::onMainPing(const std::vector<GString>& _args) {
    m_icmpClient->ping(m_hostname.c_str(), m_repetitions);
}
//===============================================
void GPocoApp::onBeginPing(const void* _sender, Poco::Net::ICMPEventArgs& _args) {
    std::ostringstream os;
    os << "Pinging " << _args.hostName() << " [" << _args.hostAddress() << "] with " << _args.dataSize() << " bytes of data:"
       << std::endl << "---------------------------------------------" << std::endl;
    logger().information(os.str());
}
//===============================================
void GPocoApp::onReplyPing(const void* _sender, Poco::Net::ICMPEventArgs& _args) {
    std::ostringstream os;
    os << "Reply from " << _args.hostAddress()
       << " bytes=" << _args.dataSize()
       << " time=" << _args.replyTime() << "ms"
       << " TTL=" << _args.ttl();
    logger().information(os.str());
}
//===============================================
void GPocoApp::onErrorPing(const void* _sender, Poco::Net::ICMPEventArgs& _args) {
    std::ostringstream os;
    os << _args.error();
    logger().information(os.str());
}
//===============================================
void GPocoApp::onEndPing(const void* _sender, Poco::Net::ICMPEventArgs& _args) {
    std::ostringstream os;
    os << std::endl << "--- Ping statistics for " << _args.hostName() << " ---"
       << std::endl << "Packets: Sent=" << _args.sent() << ", Received=" << _args.received()
       << " Lost=" << _args.repetitions() - _args.received() << " (" << 100.0 - _args.percent() << "% loss),"
       << std::endl << "Approximate round trip times in milliseconds: " << std::endl
       << "Minimum=" << _args.minRTT() << "ms, Maximum=" << _args.maxRTT()
       << "ms, Average=" << _args.avgRTT() << "ms"
       << std::endl << "------------------------------------------";
    logger().information(os.str());
}
//===============================================
void GPocoApp::initialize(Poco::Util::Application& _app) {
    loadConfiguration();
    Poco::Util::Application::initialize(_app);
    if(m_module == "ping") {
        onInitPing(_app);
    }
}
//===============================================
void GPocoApp::uninitialize() {
    if(m_module == "ping") {
        onUninitPing();
    }
}
//===============================================
int GPocoApp::main(const std::vector<GString>& _args) {
    if(m_module == "ping") {
        onMainPing(_args);
    }
    return 0;
}
//===============================================
