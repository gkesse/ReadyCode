//===============================================
#include "GMySQL.h"
#include "GLog.h"
#include "GFormat.h"
#include "GPath.h"
#include "GXml.h"
#include "GEnv.h"
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
    m_dom.reset(new GXml(GRES("xml", "pad.xml"), true));
}
//===============================================
std::string GMySQL::loadDatabase(bool _isTestEnv) const {
    std::string lDatabase = getItem("mysql", "prod_database");
    if(_isTestEnv) lDatabase = getItem("mysql", "test_database");
    return lDatabase;
}
//===============================================
GMySQL& GMySQL::openDatabase() {
    openDatabase(GEnv().isTestEnv());
    return *this;
}
//===============================================
GMySQL& GMySQL::openDatabase(bool _isTestEnv) {
    std::string lProtocol = getItem("mysql", "protocol");
    std::string lHostname = getItem("mysql", "hostname");
    std::string lPort = getItem("mysql", "port");
    std::string lUsername = getItem("mysql", "username");
    std::string lPassword = getItem("mysql", "password");
    std::string lDatabase = loadDatabase(_isTestEnv);
    openDatabase(lProtocol, lHostname, lPort, lUsername, lPassword, lDatabase);
    return *this;
}
//===============================================
GMySQL& GMySQL::openDatabase(const std::string& _protocol, const std::string& _hostname, const std::string& _port, const std::string& _username, const std::string& _password, const std::string& _database) {
    m_driver = get_driver_instance();
    std::string lHostname = sformat("%s://%s:%s/%s", _protocol.c_str(), _hostname.c_str(), _port.c_str(), _database.c_str());
    m_con.reset(m_driver->connect(lHostname, _username, _password));
    return *this;
}
//===============================================
GMySQL& GMySQL::execQuery(const std::string& _sql) {
    execQuery(_sql, GEnv().isTestEnv());
    return *this;
}
//===============================================
GMySQL& GMySQL::execQuery(const std::string& _sql, bool _isTestEnv) {
    openDatabase(_isTestEnv);
    m_stmt.reset(m_con->createStatement());
    m_stmt->execute(_sql);
    GLOGT(eGOFF, "sql..........:%s", _sql.c_str());
    return *this;
}
//===============================================
GMySQL& GMySQL::readQuery(const std::string& _sql) {
    readQuery(_sql, GEnv().isTestEnv());
    return *this;
}
//===============================================
GMySQL& GMySQL::readQuery(const std::string& _sql, bool _isTestEnv) {
    openDatabase(_isTestEnv);
    m_stmt.reset(m_con->createStatement());
    m_res.reset(m_stmt->executeQuery(_sql));
    GLOGT(eGOFF, "sql..........:%s", _sql.c_str());
    return *this;
}
//===============================================
int GMySQL::getColumnCount() const {
    int lColumns = m_res->getMetaData()->getColumnCount();
    return lColumns;
}
//===============================================
int GMySQL::getId() {
    m_res.reset(m_stmt->executeQuery("select @@identity as id"));
    m_res->next();
    int lId = (int)m_res->getInt64("id");
    return lId;
}
//===============================================
std::string GMySQL::readData(const std::string& _sql) {
    return readData(_sql, GEnv().isTestEnv());
}
//===============================================
std::string GMySQL::readData(const std::string& _sql, bool _isTestEnv) {
    readQuery(_sql, _isTestEnv);
    std::string lData = "";
    while(m_res->next()) {
        lData = m_res->getString(1);
        break;
    }
    return lData;
}
//===============================================
std::vector<std::string> GMySQL::readCol(const std::string& _sql) {
    return readCol(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<std::string> GMySQL::readCol(const std::string& _sql, bool _isTestEnv) {
    std::vector<std::string> lDataMap;
    readQuery(_sql, _isTestEnv);
    while(m_res->next()) {
        std::string lData = m_res->getString(1);
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
std::vector<std::string> GMySQL::readRow(const std::string& _sql) {
    return readRow(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<std::string> GMySQL::readRow(const std::string& _sql, bool _isTestEnv) {
    std::vector<std::string> lDataMap;
    readQuery(_sql, _isTestEnv);
    int lColumns = getColumnCount();
    while(m_res->next()) {
        for(int i = 1; i <= lColumns; i++) {
            std::string lData = m_res->getString(i);
            lDataMap.push_back(lData);
        }
        break;
    }
    return lDataMap;
}
//===============================================
std::vector<std::vector<std::string>> GMySQL::readMap(const std::string& _sql) {
    return readMap(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<std::vector<std::string>> GMySQL::readMap(const std::string& _sql, bool _isTestEnv) {
    std::vector<std::vector<std::string>> lDataMap;
    readQuery(_sql, _isTestEnv);
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
