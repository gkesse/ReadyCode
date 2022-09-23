//===============================================
#include "GMySQL2.h"
#include "GLog.h"
#include "GPath.h"
#include "GCode2.h"
#include "GEnv.h"
//===============================================
GMySQL2::GMySQL2()
: GObject2() {
    createDoms();
    deserializeDom();
    m_driver = 0;
}
//===============================================
GMySQL2::~GMySQL2() {

}
//===============================================
GString2 GMySQL2::serialize(const GString2& _code) const {
    GCode2 lDom;
    lDom.createDoc();
    lDom.addData(_code, "protocol", m_protocol);
    lDom.addData(_code, "hostname", m_hostname);
    lDom.addData(_code, "port", m_port);
    lDom.addData(_code, "username", m_username);
    lDom.addData(_code, "password", m_password);
    lDom.addData(_code, "prod_database", m_databaseProd);
    lDom.addData(_code, "test_database", m_databaseTest);
    return lDom.toString();
}
//===============================================
bool GMySQL2::deserialize(const GString2& _data, const GString2& _code) {
    GCode2 lDom;
    lDom.loadXml(_data);
    m_protocol = lDom.getData(_code, "protocol");
    m_hostname = lDom.getData(_code, "hostname");
    m_port = lDom.getData(_code, "port");
    m_username = lDom.getData(_code, "username");
    m_password = lDom.getData(_code, "password");
    m_databaseProd = lDom.getData(_code, "prod_database");
    m_databaseTest = lDom.getData(_code, "test_database");
    return true;
}
//===============================================
bool GMySQL2::deserializeDom(const GString2& _code) {
    GString2 lData = m_dom->toString();
    deserialize(lData, _code);
    return true;
}
//===============================================
GString2 GMySQL2::loadDatabase(bool _isTestEnv) const {
    if(_isTestEnv) return m_databaseTest;
    return m_databaseProd;
}
//===============================================
bool GMySQL2::openDatabase() {
    if(!openDatabase(GEnv().isTestEnv())) return false;
    return true;
}
//===============================================
bool GMySQL2::openDatabase(bool _isTestEnv) {
    GString2 lDatabase = loadDatabase(_isTestEnv);
    if(!openDatabase(m_protocol, m_hostname, m_port, m_username, m_password, lDatabase)) return false;
    return true;
}
//===============================================
bool GMySQL2::openDatabase(const GString2& _protocol, const GString2& _hostname, const GString2& _port, const GString2& _username, const GString2& _password, const GString2& _database) {
    m_driver = get_driver_instance();
    GString2 lHostname = sformat("%s://%s:%s/%s", _protocol.c_str(), _hostname.c_str(), _port.c_str(), _database.c_str());
    m_con.reset(m_driver->connect(lHostname.c_str(), _username.c_str(), _password.c_str()));
    return true;
}
//===============================================
GMySQL2& GMySQL2::execQuery(const GString2& _sql) {
    execQuery(_sql, GEnv().isTestEnv());
    return *this;
}
//===============================================
GMySQL2& GMySQL2::execQuery(const GString2& _sql, bool _isTestEnv) {
    GLOGT(eGMSG, "%s", _sql.c_str());
    openDatabase(_isTestEnv);
    m_stmt.reset(m_con->createStatement());
    m_stmt->execute(_sql.c_str());
    return *this;
}
//===============================================
bool GMySQL2::readQuery(const GString2& _sql) {
    if(!readQuery(_sql, GEnv().isTestEnv())) return false;
    return true;
}
//===============================================
bool GMySQL2::readQuery(const GString2& _sql, bool _isTestEnv) {
    GLOGT(eGMSG, "%s", _sql.c_str());
    if(!openDatabase(_isTestEnv)) return false;
    m_stmt.reset(m_con->createStatement());
    m_res.reset(m_stmt->executeQuery(_sql.c_str()));
    return true;
}
//===============================================
int GMySQL2::getColumnCount() const {
    int lColumns = m_res->getMetaData()->getColumnCount();
    return lColumns;
}
//===============================================
int GMySQL2::getId() {
    m_res.reset(m_stmt->executeQuery("select @@identity as id"));
    m_res->next();
    int lId = (int)m_res->getInt64("id");
    return lId;
}
//===============================================
GString2 GMySQL2::readData(const GString2& _sql) {
    return readData(_sql, GEnv().isTestEnv());
}
//===============================================
GString2 GMySQL2::readData(const GString2& _sql, bool _isTestEnv) {
    GString2 lData = "";
    if(!readQuery(_sql, _isTestEnv)) return lData;
    while(m_res->next()) {
        lData = m_res->getString(1);
        break;
    }
    return lData;
}
//===============================================
std::vector<GString2> GMySQL2::readCol(const GString2& _sql) {
    return readCol(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<GString2> GMySQL2::readCol(const GString2& _sql, bool _isTestEnv) {
    std::vector<GString2> lDataMap;
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
    while(m_res->next()) {
        GString2 lData = m_res->getString(1).c_str();
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
std::vector<GString2> GMySQL2::readRow(const GString2& _sql) {
    return readRow(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<GString2> GMySQL2::readRow(const GString2& _sql, bool _isTestEnv) {
    std::vector<GString2> lDataMap;
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
    int lColumns = getColumnCount();
    while(m_res->next()) {
        for(int i = 1; i <= lColumns; i++) {
            GString2 lData = m_res->getString(i).c_str();
            lDataMap.push_back(lData);
        }
        break;
    }
    return lDataMap;
}
//===============================================
std::vector<std::vector<GString2>> GMySQL2::readMap(const GString2& _sql) {
    return readMap(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<std::vector<GString2>> GMySQL2::readMap(const GString2& _sql, bool _isTestEnv) {
    std::vector<std::vector<GString2>> lDataMap;
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
    int lColumns = getColumnCount();
    while(m_res->next()) {
        std::vector<GString2> lDataRow;
        for(int i = 1; i <= lColumns; i++) {
            GString2 lData = m_res->getString(i).c_str();
            lDataRow.push_back(lData);
        }
        lDataMap.push_back(lDataRow);
    }
    return lDataMap;
}
//===============================================