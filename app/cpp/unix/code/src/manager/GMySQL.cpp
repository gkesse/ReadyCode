//===============================================
#include "GMySQL.h"
#include "GLog.h"
#include "GFormat.h"
#include "GPath.h"
#include "GXml.h"
//===============================================
GMySQL::GMySQL() : GObject() {
    createDoms();
    //
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
void GMySQL::createDoms() {
    if(GLOGI->hasError()) return;
    m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
GMySQL& GMySQL::openDatabase() {
    if(GLOGI->hasError()) return *this;
    std::string lHostname = getItem("mysql", "hostname");
    std::string lPort = getItem("mysql", "port");
    std::string lUsername = getItem("mysql", "username");
    std::string lPassword = getItem("mysql", "password");
    openDatabase(lHostname, lPort, lUsername, lPassword);
    return *this;
}
//===============================================
GMySQL& GMySQL::openDatabase(const std::string& _hostname, const std::string& _port, const std::string& _username, const std::string& _password) {
    if(GLOGI->hasError()) return *this;
    m_driver = get_driver_instance();
    std::string lHostname = sformat("tcp://%s:%s", _hostname.c_str(), _port.c_str());
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
