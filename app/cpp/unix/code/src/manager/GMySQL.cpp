//===============================================
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GPath.h"
#include "GEnv.h"
//===============================================
GMySQL::GMySQL()
: GObject() {
    createDoms();
    deserializeDom();
    m_driver = 0;
}
//===============================================
GMySQL::~GMySQL() {

}
//===============================================
GString GMySQL::serialize(const GString& _code) const {
    GCode lDom;
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
bool GMySQL::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
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
bool GMySQL::deserializeDom(const GString& _code) {
    GString lData = m_dom->toString();
    deserialize(lData, _code);
    return true;
}
//===============================================
GString GMySQL::loadDatabase(bool _isTestEnv) const {
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
    GString lDatabase = loadDatabase(_isTestEnv);
    if(!openDatabase(m_protocol, m_hostname, m_port, m_username, m_password, lDatabase)) return false;
    return true;
}
//===============================================
bool GMySQL::openDatabase(const GString& _protocol, const GString& _hostname, const GString& _port, const GString& _username, const GString& _password, const GString& _database) {
    m_driver = get_driver_instance();
    GString lHostname = GFORMAT("%s://%s:%s/%s", _protocol.c_str(), _hostname.c_str(), _port.c_str(), _database.c_str());
    m_con.reset(m_driver->connect(lHostname.c_str(), _username.c_str(), _password.c_str()));
    return true;
}
//===============================================
bool GMySQL::execQuery(const GString& _sql) {
    if(!execQuery(_sql, GEnv().isTestEnv())) return false;
    return true;
}
//===============================================
bool GMySQL::execQuery(const GString& _sql, bool _isTestEnv) {
    GLOGT(eGMSG, "%s", _sql.c_str());
    try {
        openDatabase(_isTestEnv);
        m_stmt.reset(m_con->createStatement());
        m_stmt->execute(_sql.c_str());
    }
    catch (sql::SQLException &e) {
        GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête SQL.\n%s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr());
        return false;
    }
    return true;
}
//===============================================
bool GMySQL::readQuery(const GString& _sql) {
    if(!readQuery(_sql, GEnv().isTestEnv())) return false;
    return true;
}
//===============================================
bool GMySQL::readQuery(const GString& _sql, bool _isTestEnv) {
    GLOGT(eGMSG, "%s", _sql.c_str());
    try {
        openDatabase(_isTestEnv);
        m_stmt.reset(m_con->createStatement());
        m_res.reset(m_stmt->executeQuery(_sql.c_str()));
    }
    catch (sql::SQLException &e) {
        GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête SQL.\n%s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr());
        return false;
    }
    return true;
}
//===============================================
int GMySQL::getColumnCount() const {
    int lColumns = m_res->getMetaData()->getColumnCount();
    return lColumns;
}
//===============================================
int GMySQL::getId() {
    int lId = 0;
    try {
        m_res.reset(m_stmt->executeQuery("select @@identity as id"));
        m_res->next();
        lId = (int)m_res->getInt64("id");
    }
    catch (sql::SQLException &e) {
        GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête SQL.\n%s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr());
    }
    return lId;
}
//===============================================
GString GMySQL::readData(const GString& _sql) {
    return readData(_sql, GEnv().isTestEnv());
}
//===============================================
GString GMySQL::readData(const GString& _sql, bool _isTestEnv) {
    GString lData = "";
    if(!readQuery(_sql, _isTestEnv)) return lData;
    while(m_res->next()) {
        lData = m_res->getString(1);
        break;
    }
    return lData;
}
//===============================================
std::vector<GString> GMySQL::readCol(const GString& _sql) {
    return readCol(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<GString> GMySQL::readCol(const GString& _sql, bool _isTestEnv) {
    std::vector<GString> lDataMap;
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
    while(m_res->next()) {
        GString lData = m_res->getString(1).c_str();
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
std::vector<GString> GMySQL::readRow(const GString& _sql) {
    return readRow(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<GString> GMySQL::readRow(const GString& _sql, bool _isTestEnv) {
    std::vector<GString> lDataMap;
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
    int lColumns = getColumnCount();
    while(m_res->next()) {
        for(int i = 1; i <= lColumns; i++) {
            GString lData = m_res->getString(i).c_str();
            lDataMap.push_back(lData);
        }
        break;
    }
    return lDataMap;
}
//===============================================
std::vector<std::vector<GString>> GMySQL::readMap(const GString& _sql) {
    return readMap(_sql, GEnv().isTestEnv());
}
//===============================================
std::vector<std::vector<GString>> GMySQL::readMap(const GString& _sql, bool _isTestEnv) {
    std::vector<std::vector<GString>> lDataMap;
    if(!readQuery(_sql, _isTestEnv)) return lDataMap;
    int lColumns = getColumnCount();
    while(m_res->next()) {
        std::vector<GString> lDataRow;
        for(int i = 1; i <= lColumns; i++) {
            GString lData = m_res->getString(i).c_str();
            lDataRow.push_back(lData);
        }
        lDataMap.push_back(lDataRow);
    }
    return lDataMap;
}
//===============================================
