//===============================================
#include "GMySQL.h"
#include "GLog.h"
#include "GFormat.h"
#include "GPath.h"
#include "GXml.h"
//===============================================
GMySQL::GMySQL() : GObject() {
    createDoms();
    m_driver = 0;
}
//===============================================
GMySQL::~GMySQL() {

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
    std::string lProtocol = getItem("mysql", "protocol");
    std::string lHostname = getItem("mysql", "hostname");
    std::string lPort = getItem("mysql", "port");
    std::string lUsername = getItem("mysql", "username");
    std::string lPassword = getItem("mysql", "password");
    std::string lDatabase = getItem("mysql", "database");
    openDatabase(lProtocol, lHostname, lPort, lUsername, lPassword, lDatabase);
    return *this;
}
//===============================================
GMySQL& GMySQL::openDatabase(const std::string& _protocol, const std::string& _hostname, const std::string& _port, const std::string& _username, const std::string& _password, const std::string& _database) {
    if(GLOGI->hasError()) return *this;
    m_driver = get_driver_instance();
    std::string lHostname = sformat("%s://%s:%s/%s", _protocol.c_str(), _hostname.c_str(), _port.c_str(), _database.c_str());
    m_con.reset(m_driver->connect(lHostname, _username, _password));
    return *this;
}
//===============================================
GMySQL& GMySQL::execQuery(const std::string& _sql) {
    if(GLOGI->hasError()) return *this;
    openDatabase();
    m_stmt.reset(m_con->createStatement());
    m_res.reset(m_stmt->executeQuery(_sql));
    return *this;
}
//===============================================
int GMySQL::getColumnCount() const {
    if(GLOGI->hasError()) return 0;
    int lColumns = m_res->getMetaData()->getColumnCount();
    return lColumns;
}
//===============================================
std::string GMySQL::readData(const std::string& _sql) {
    if(GLOGI->hasError()) return "";
    execQuery(_sql);
    std::string lData = "";
    while(m_res->next()) {
        lData = m_res->getString(1);
        break;
    }
    return lData;
}
//===============================================
std::vector<std::string> GMySQL::readCol(const std::string& _sql) {
    std::vector<std::string> lDataMap;
    if(GLOGI->hasError()) return lDataMap;
    execQuery(_sql);
    while(m_res->next()) {
        std::string lData = m_res->getString(1);
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
std::vector<std::string> GMySQL::readRow(const std::string& _sql) {
    std::vector<std::string> lDataMap;
    if(GLOGI->hasError()) return lDataMap;
    execQuery(_sql);
    while(m_res->next()) {
        std::string lData = m_res->getString(1);
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
std::vector<std::vector<std::string>> GMySQL::readMap(const std::string& _sql) {
    std::vector<std::vector<std::string>> lDataMap;
    if(GLOGI->hasError()) return lDataMap;
    execQuery(_sql);
    int lColumns = getColumnCount();
    while(m_res->next()) {
        std::vector<std::string> lDataRow;
        for(int i = 1; i <= lColumns; i++) {
            std::string lData = m_res->getString(i);
            lDataRow.push_back(lData);
        }
        lDataMap.push_back(lDataRow);
    }
    return lDataMap;
}
//===============================================
