//===============================================
#ifndef _GDescriptor_
#define _GDescriptor_
//===============================================
#include "GObject.h"
//===============================================
#define GDESCRIPTOR GDescriptor::Instance()
//===============================================
class GDescriptor : public GObject {
public:
    GDescriptor();
    ~GDescriptor();
    //
    void initDescriptor();
    void initTimeout(int _ms);
    void enableDescriptor(int _socket);
    bool selectDescriptor();
    bool setOption(int _socket);
    int getOption(int _socket) const;

private:
    fd_set m_descriptor;
    struct timeval m_timeout;
};
//==============================================
#endif
//==============================================
