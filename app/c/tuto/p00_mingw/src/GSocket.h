//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
typedef struct _GSocket GSocket;
//===============================================
struct _GSocket {
    void (*delete)(GSocket** _this);
    void (*run)(GSocket* _this);
    void (*read)(GSocket* _this, GString* _data);
    void (*send)(GSocket* _this, const char* _data);

    GObject* m_obj;
    SOCKET m_socket;
};
//===============================================
void GSocket_init(GSocket* _this);
GSocket* GSocket_new();
//===============================================
#endif
//===============================================
