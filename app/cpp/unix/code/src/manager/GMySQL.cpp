//===============================================
#include "GMySQL.h"
#include "GCode.h"
#include "GLog.h"
#include "GPath.h"
#include "GEnv.h"
//===============================================
GMySQL::GMySQL(const GString& _code)
: GObject(_code) {
    createDoms();
    initMySQL();
}
//===============================================
GMySQL::~GMySQL() {

}
//===============================================
void GMySQL::initMySQL() {
    m_isTestEnv     = GEnv().isTestEnv();

    m_protocol      = m_dom->getData("socket", "protocol");
    m_hostname      = m_dom->getData("socket", "hostname");
    m_port          = m_dom->getData("socket", "port").toInt();
    m_username      = m_dom->getData("socket", "username");
    m_password      = m_dom->getData("socket", "password");
    m_databaseProd  = m_dom->getData("socket", "database_prod");
    m_databaseTest  = m_dom->getData("socket", "database_test");
    m_database      = (m_isTestEnv ? m_databaseTest : m_databaseProd);
    m_logOn         = m_dom->getData("socket", "log_on").toInt();

    m_driver = 0;
}
//===============================================
bool GMySQL::openDatabase() {
    if(m_protocol == "") return false;
    if(m_hostname == "") return false;
    if(m_database == "") return false;
    if(m_username == "") return false;
    if(m_password == "") return false;
    if(m_port <= 0) return false;

    m_driver = get_driver_instance();
    GString lHostname = GFORMAT("%s://%s:%d/%s", m_protocol.c_str(), m_hostname.c_str(), m_port, m_database.c_str());
    m_con.reset(m_driver->connect(lHostname.c_str(), m_username.c_str(), m_password.c_str()));
    return true;
}
//===============================================
bool GMySQL::execQuery(const GString& _sql) {
    if(m_logOn) GLOGT(eGMSG, "%s", _sql.c_str());
    try {
        openDatabase();
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
    if(m_logOn) GLOGT(eGMSG, "%s", _sql.c_str());
    try {
        openDatabase();
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
    GString lData;
    if(!readQuery(_sql)) return lData;
    while(m_res->next()) {
        lData = m_res->getString(1);
        break;
    }
    return lData;
}
//===============================================
std::vector<GString> GMySQL::readCol(const GString& _sql) {
    std::vector<GString> lDataMap;
    if(!readQuery(_sql)) return lDataMap;
    while(m_res->next()) {
        GString lData = m_res->getString(1).c_str();
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
std::vector<GString> GMySQL::readRow(const GString& _sql) {
    std::vector<GString> lDataMap;
    if(!readQuery(_sql)) return lDataMap;
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
    std::vector<std::vector<GString>> lDataMap;
    if(!readQuery(_sql)) return lDataMap;
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
