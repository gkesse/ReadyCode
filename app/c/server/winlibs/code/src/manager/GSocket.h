//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GSocket GSocket;
//===============================================
struct _GSocket {
    GObject* m_obj;
    SOCKET m_socket;

    void (*delete)(GSocket* _this);
    void (*runServer)(GSocket* _this, int _argc, char** _argv);
    void (*callServer)(GSocket* _this, const char* _data, GString* _dataOut);
    GString* (*callFacade)(GSocket* _this, const char* _module, const char* _method, const char* _params);
    void (*read)(GSocket* _this, GString* _data);
    void (*send)(GSocket* _this, const char* _data);
};
//===============================================
GSocket* GSocket_new();
//===============================================
#endif
//===============================================
