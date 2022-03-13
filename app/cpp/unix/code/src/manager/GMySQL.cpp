//===============================================
#include "GMySQL.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GMySQL::GMySQL() : GObject() {
    m_driver = 0;
    m_con = 0;
    m_stmt = 0;
    m_res = 0;
}
//===============================================
GMySQL::~GMySQL() {
    delete m_con;
}
//===============================================
GMySQL& GMySQL::openDatabase(const std::string& _hostname, int _port, const std::string& _username, const std::string& _password) {
    if(GLOGI->hasError()) return *this;
    m_driver = get_driver_instance();
    std::string lHostname = sformat("tpc://%s:%d", _hostname.c_str(), _port);
    m_con = m_driver->connect(lHostname, _username, _password);
    if(!m_con) {
        GLOG("Erreur la methode (GMySQL::openDatabase) a echoue (1)\n"
                "- hostname......: (%s)\n"
                "- username......: (%s)\n"
                "- password......: (%s)", lHostname.c_str(), _username.c_str(), _password.c_str());
        return *this;
    }
    return *this;
}
//===============================================
