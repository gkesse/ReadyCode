//===============================================
#ifndef _GStruct_
#define _GStruct_
//===============================================
#include "GInclude.h"
//===============================================
struct sGQt;
struct sGXml;
struct sGSocket;
struct sGSQLite;
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
    bool hostname_on;
    int port;
    int backlog;
    int major;
    int minor;
    void* on_start;
    sGSocket();
};
//===============================================
struct sGSQLite {
    std::string version;
    std::vector<std::string>* names;
    std::string data_val;
    std::vector<std::string> data_list;
    std::vector<std::vector<std::string>> data_map;
    int row_count;
    bool names_on;
    sGSQLite();
};
//==============================================
#endif
//==============================================
