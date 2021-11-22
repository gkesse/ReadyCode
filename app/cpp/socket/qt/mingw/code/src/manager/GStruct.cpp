//===============================================
#include "GStruct.h"
//===============================================
sGQt::sGQt() {
    app_name = "ReadyApp";
    width = 400;
    height = 400;
}
//===============================================
sGXml::sGXml() {
    indent = 4;
}
//===============================================
sGSocket::sGSocket() {
    address_ip = "0.0.0.0";
    port = 8585;
    backlog = 10;
    major = 2;
    minor = 2;
    on_start = 0;
    socket = 0;
    hostname_on = false;
}
//===============================================
sGSQLite::sGSQLite() {
    row_count = 0;
    names = 0;
    names_on = true;
}
//===============================================
