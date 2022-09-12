//===============================================
#ifndef _GPocoReactor_
#define _GPocoReactor_
//===============================================
#include "GObject.h"
//===============================================
class GPocoReactor : public GObject {
public:
    GPocoReactor(Poco::Net::StreamSocket& _socket, Poco::Net::SocketReactor& _reactor);
    ~GPocoReactor();

protected:
    void onFIFOOutReadable(bool& b);
    void onFIFOInWritable(bool& b);
    void onSocketReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf);
    void onSocketWritable(const Poco::AutoPtr<Poco::Net::WritableNotification>& pNf);
    void onSocketShutdown(const Poco::AutoPtr<Poco::Net::ShutdownNotification>& pNf);

private:
    static const int BUFFER_SIZE = 10;
    Poco::Net::StreamSocket m_socket;
    Poco::Net::SocketReactor& m_reactor;
    Poco::FIFOBuffer m_dataIn;
    Poco::FIFOBuffer m_dataOut;
    std::string m_hostname;
};
//==============================================
#endif
//==============================================
