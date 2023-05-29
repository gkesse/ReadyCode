//===============================================
#ifndef _GServer_
#define _GServer_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GServer GServer;
typedef struct _GSocket GSocket;
typedef struct _GManager GManager;
typedef struct _GCode GCode;
//===============================================
struct _GServer {
    GManager* m_mgr;
    SOCKET m_socket;
    GCode* m_rep;

    void (*delete)(GServer* _this);
    void (*run)(GServer* _this, GString* _data);
    void (*send)(GServer* _this, GSocket* _socket);
};
//===============================================
GServer* GServer_new();
//===============================================
#endif
//===============================================
