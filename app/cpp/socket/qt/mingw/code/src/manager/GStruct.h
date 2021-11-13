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
    QHostAddress address;
    int port;
    sGSocket();
};
//==============================================
#endif
//==============================================
