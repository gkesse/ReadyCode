//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GServer GServer;
typedef struct _GSocket GSocket;
//===============================================
struct _GServer {
    GObject* m_parent;
    SOCKET m_socket;

    void (*delete)(GServer* _this);
    void (*run)(GServer* _this, GString* _data);
    void (*send)(GServer* _this, GSocket* _socket);
};
//===============================================
GServer* GServer_new();
//===============================================
#endif
//===============================================