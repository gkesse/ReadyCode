//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GSocket GSocket;
//===============================================
struct _GSocket {
    GObject* m_parent;
    SOCKET m_socket;

    void (*delete)(GSocket* _this);
    void (*run)(GSocket* _this, int _argc, char** _argv);
    void (*callServer)(GSocket* _this, const char* _data);
};
//===============================================
GSocket* GSocket_new();
//===============================================
#endif
//===============================================
