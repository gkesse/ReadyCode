//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
#include "GInclude.h"
//===============================================
struct sGQt;
struct sGXml;
struct sGSocket;
//===============================================
class GSocket;
//===============================================
struct sGQt {
    QString app_name;
    int width;
    int height;
    sGQt();
};
//===============================================
struct sGXml {
    int indent;
    sGXml();
};
//===============================================
struct sGSocket {
    GSocket* socket;
    std::string address_ip;
    std::string hostname;
    std::string client_ip;
    int port;
    int backlog;
    int major;
    int minor;
    void* on_start;
    sGSocket();
};
//==============================================
#endif
//==============================================
