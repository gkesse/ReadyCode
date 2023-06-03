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
    GObject* m_obj;
    SOCKET m_socket;

    void (*delete)(GServer* _this);
    void (*send)(GServer* _this, GSocket* _socket);
    void (*run)(GServer* _this, const char* _data);
    void (*runCalculator)(GServer* _this, const char* _data);
};
//===============================================
GServer* GServer_new();
//===============================================
#endif
//===============================================
