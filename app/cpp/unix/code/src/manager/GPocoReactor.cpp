//===============================================
#include "GPocoReactor.h"
#include "GLog.h"
//===============================================
GPocoReactor::GPocoReactor(Poco::Net::StreamSocket& _socket, Poco::Net::SocketReactor& _reactor)
: GObject()
, m_socket(_socket)
, m_reactor(_reactor)
, m_dataIn(BUFFER_SIZE, true)
, m_dataOut(BUFFER_SIZE, true) {
    Poco::Util::Application& lApp = Poco::Util::Application::instance();
    m_hostname = m_socket.peerAddress().toString();
    lApp.logger().information(GFORMAT("Connection from %", m_hostname.c_str()).c_str());

    m_reactor.addEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::ReadableNotification>(*this, &GPocoReactor::onSocketReadable));
    m_reactor.addEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::ShutdownNotification>(*this, &GPocoReactor::onSocketShutdown));
    m_dataOut.readable += Poco::delegate(this, &GPocoReactor::onFIFOOutReadable);
    m_dataIn.writable += Poco::delegate(this, &GPocoReactor::onFIFOInWritable);
}
//===============================================
GPocoReactor::~GPocoReactor() {
    Poco::Util::Application& lApp = Poco::Util::Application::instance();
    try {
        m_hostname = m_socket.peerAddress().toString();
        lApp.logger().information("Disconnecting " + m_hostname.c_str());
    }
    catch (...) {
    }

    m_reactor.removeEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::ReadableNotification>(*this, &GPocoReactor::onSocketReadable));
    m_reactor.removeEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::WritableNotification>(*this, &GPocoReactor::onSocketWritable));
    m_reactor.removeEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::ShutdownNotification>(*this, &GPocoReactor::onSocketShutdown));

    m_dataOut.readable -= Poco::delegate(this, &GPocoReactor::onFIFOOutReadable);
    m_dataOut.writable -= Poco::delegate(this, &GPocoReactor::onFIFOInWritable);
}
//===============================================
void GPocoReactor::onFIFOOutReadable(bool& b) {
    if (b)
        m_reactor.addEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::WritableNotification>(*this, &GPocoReactor::onSocketWritable));
    else
        m_reactor.removeEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::WritableNotification>(*this, &GPocoReactor::onSocketWritable));
}
//===============================================
void GPocoReactor::onFIFOInWritable(bool& b) {
    if (b)
        m_reactor.addEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::ReadableNotification>(*this, &GPocoReactor::onSocketReadable));
    else
        m_reactor.removeEventHandler(m_socket, Poco::NObserver<GPocoReactor, Poco::Net::ReadableNotification>(*this, &GPocoReactor::onSocketReadable));
}
//===============================================
void GPocoReactor::onSocketReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf) {
    try {
        int len = m_socket.receiveBytes(m_dataIn);
        if (len > 0) {
            m_dataIn.drain(m_dataOut.write(m_dataIn.buffer(), m_dataIn.used()));
        }
        else {
            delete this;
        }
    }
    catch (Poco::Exception& exc) {
        Poco::Util::Application& lApp = Poco::Util::Application::instance();
        lApp.logger().log(exc);
        delete this;
    }
}
//===============================================
void GPocoReactor::onSocketWritable(const Poco::AutoPtr<Poco::Net::WritableNotification>& pNf) {
    try {
        m_socket.sendBytes(m_dataOut);
    }
    catch (Poco::Exception& exc) {
        Poco::Util::Application& lApp = Poco::Util::Application::instance();
        lApp.logger().log(exc);
        delete this;
    }
}
//===============================================
void GPocoReactor::onSocketShutdown(const Poco::AutoPtr<Poco::Net::ShutdownNotification>& pNf) {
    delete this;
}
//===============================================
