//===============================================
#include "GMySQL.h"
#include "GLog.h"
#include "GFormat.h"
#include "GPath.h"
#include "GCode.h"
#include "GEnv.h"
//===============================================
GMySQL::GMySQL() : GObject() {
    createDoms();
    deserializeDom();
    m_driver = 0;
}
//===============================================
GMySQL::~GMySQL() {

}
//===============================================
std::string GMySQL::serialize(const std::string& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "protocol", m_protocol);
    lDom.addData(_code, "hostname", m_hostname);
    lDom.addData(_code, "port", m_port);
    lDom.addData(_code, "username", m_username);
    lDom.addData(_code, "password", m_password);
    lDom.addData(_code, "prod_database", m_databaseProd);
    lDom.addData(_code, "test_database", m_databaseTest);
    return lDom.toStringData();
}
//===============================================
void GMySQL::deserialize(const std::string& _data, const std::string& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_protocol = lDom.getItem(_code, "protocol");
    m_hostname = lDom.getItem(_code, "hostname");
    m_port = lDom.getItem(_code, "port");
    m_username = lDom.getItem(_code, "username");
    m_password = lDom.getItem(_code, "password");
    m_databaseProd = lDom.getItem(_code, "prod_database");
    m_databaseTest = lDom.getItem(_code, "test_database");
}
//===============================================
void GMySQL::deserializeDom(const std::string& _code) {
    std::string lData = m_dom->toString();
    deserialize(lData, _code);
}
//===============================================
std::string GMySQL::loadDatabase(bool _isTestEnv) const {
    if(_isTestEnv) return m_databaseTest;
    return m_databaseProd;
}
//===============================================
bool GMySQL::openDatabase() {
    if(!openDatabase(GEnv().isTestEnv())) return false;
    return true;
}
//===============================================
bool GMySQL::openDatabase(bool _isTestEnv) {
    std::string lDatabase = loadDatabase(_isTestEnv);
    if(!openDatabase(m_protocol, m_hostname, m_port, m_username, m_password, lDatabase)) return false;
    return true;
}
//===============================================
bool GMySQL::openDatabase(const std::string& _protocol, const std::string& _hostname, const std::string& _port, const std::string& _username, const std::string& _password, const std::string& _database) {
    m_driver = get_driver_instance();
    std::string lHostname = sformat("%s://%s:%s/%s", _protocol.c_str(), _hostname.c_str(), _port.c_str(), _database.c_str());
    m_con.reset(m_driver->connect(lHostname, _username, _password));
    return true;
}
//===============================================
bool GMySQL::execQuery(const std::string& _sql) {
    if(!execQuery(_sql, GEnv().isTestEnv())) return false;
    return true;
}
//===============================================
bool GMySQL::execQuery(const std::string& _sql, bool _isTestEnv) {
    GLOGT(eGMSG, "%s", _sql.c_str());
    if(!openDatabase(_isTestEnv)) return false;
    m_stmt.reset(m_con->createStatement());
    m_stmt->execute(_sql);
    return true;
}
//===============================================
bool GMySQL::readQuery(const std::string& _sql) {
    if(!readQuery(_sql, GEnv().isTestEnv())) return false;
    return true;
}
//===============================================
bool GMySQL::readQuery(const std::string& _sql, bool _isTestEnv) {
    GLOGT(eGMSG, "%s", _sql.c_str());
    if(!openDatabase(_isTestEnv)) return false;
    m_stmt.reset(m_con->createStatement());
    m_res.reset(m_stmt->executeQuery(_sql));
    return true;
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
    std::string lData = "";
    if(!readQuery(_sql, _isTestEnv)) return lData;
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
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
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
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
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
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
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
