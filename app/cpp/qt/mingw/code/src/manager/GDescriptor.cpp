//===============================================
#include "GDescriptor.h"
//===============================================
GDescriptor::GDescriptor() : GObject() {

}
//===============================================
GDescriptor::~GDescriptor() {

}
//===============================================
void GDescriptor::initDescriptor() {
    FD_ZERO(&m_descriptor);
}
//===============================================
void GDescriptor::initTimeout(int _ms) {
    m_timeout.tv_sec = static_cast<long>(_ms / 1000);
    m_timeout.tv_usec = static_cast<long>((_ms % 1000) * 1000);
}
//===============================================
void GDescriptor::enableDescriptor(int _socket) {
    FD_SET(_socket, &m_descriptor);
}
//===============================================
bool GDescriptor::selectDescriptor() {
    int lStatus = select(0, &m_descriptor, 0, 0, &m_timeout);
    if(lStatus == 0) {
        return false;
    }
    if(lStatus == SOCKET_ERROR) {
        return false;
    }
    return true;
}
//===============================================
bool GDescriptor::setOption(int _socket) {
    int lOptionVal = 1;
    int lStatus = setsockopt(_socket, SOL_SOCKET, SO_OOBINLINE, reinterpret_cast<const char*>(&lOptionVal), sizeof(int));
    if(lStatus == SOCKET_ERROR) {
        return false;
    }
    return true;
}
//===============================================
int GDescriptor::getOption(int _socket) const {
    int lError;
    int lLength = sizeof(lError);
    int lOption = getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char*)&lError, &lLength);
    return lOption;
}
//===============================================
