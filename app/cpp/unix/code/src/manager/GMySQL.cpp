//===============================================
#include "GMySQL.h"
#include "GCode.h"
#include "GPath.h"
#include "GEnv.h"
#include "GApp.h"
//===============================================
GMySQL* GMySQL::m_instance = 0;
//===============================================
GMySQL::GMySQL(bool _hasLog)
: GObject() {
    initMySQL();
    m_hasLog = _hasLog;
}
//===============================================
GMySQL::~GMySQL() {

}
//===============================================
GMySQL* GMySQL::Instance() {
    if(m_instance == 0) {
        m_instance = new GMySQL;
    }
    return m_instance;
}
//===============================================
void GMySQL::initMySQL() {
    bool lIsTestEnv = GENV->isTestEnv();
    GString lDatabaseProd = GAPP->getData("mysql", "database_prod");
    GString lDatabaseTest = GAPP->getData("mysql", "database_test");

    m_protocol      = GAPP->getData("mysql", "protocol");
    m_hostname      = GAPP->getData("mysql", "hostname");
    m_port          = GAPP->getData("mysql", "port").toInt();
    m_username      = GAPP->getData("mysql", "username");
    m_password      = GAPP->getData("mysql", "password");
    m_database      = (lIsTestEnv ? lDatabaseTest : lDatabaseProd);
}
//===============================================
void GMySQL::setAction(const GString& _action) {
    m_action = _action;
}
//===============================================
void GMySQL::setSql(const GString& _sql) {
    m_sql = _sql;
    if(m_hasLog) {
        GLOGT(eGMSG, "%s", _sql.c_str());
    }
}
//===============================================
GString GMySQL::convertZeroToNull(int _data) {
    if(_data == 0) return "null";
    return _data;
}
//===============================================
bool GMySQL::openDatabase() {
    if(m_protocol.isEmpty()) {
        m_logs.addError("Le protocol est obligatoire.");
        return false;
    }
    if(m_hostname.isEmpty()) {
        m_logs.addError("Le nom de la machine est obligatoire.");
        return false;
    }
    if(m_database.isEmpty()) {
        m_logs.addError("La base de donnée est obligatoire.");
        return false;
    }
    if(m_username.isEmpty()) {
        m_logs.addError("Le nom d'utilisateur est obligatoire.");
        return false;
    }
    if(m_password.isEmpty()) {
        m_logs.addError("Le mot de passe est obligatoire.");
        return false;
    }
    if(!m_port) {
        m_logs.addError("Le port est obligatoire.");
        return false;
    }

    m_driver = get_driver_instance();
    GString lHostname = GFORMAT("%s://%s:%d/%s", m_protocol.c_str(), m_hostname.c_str(), m_port, m_database.c_str());
    m_con.reset(m_driver->connect(lHostname.c_str(), m_username.c_str(), m_password.c_str()));
    return !m_logs.hasErrors();
}
//===============================================
bool GMySQL::execQuery(const GString& _sql) {
    setSql(_sql);
    setAction("write");
    if(!run()) return false;
    return !m_logs.hasErrors();
}
//===============================================
bool GMySQL::run() {
    if(m_action.isEmpty()) {
        m_logs.addError("L'action est obligatoire.");
        return false;
    }
    if(m_sql.isEmpty()) {
        m_logs.addError("La requête SQL est obligatoire.");
        return false;
    }
    if(m_action == "write") {
        runWrite();
    }
    else if(m_action == "read") {
        runRead();
    }
    else {
        m_logs.addError("L'action est inconnue.");
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GMySQL::runWrite() {
    try {
        if(!openDatabase()) return false;
        m_stmt.reset(m_con->createStatement());
        m_stmt->execute(m_sql.c_str());
    }
    catch (sql::SQLException &e) {
        if(e.getErrorCode() == 1062) {
            m_logs.addError("Cette donnée existe déjà.");
        }
        else {
            m_logs.addError("L'opération a rencontré un problème.");
        }
        GLOGT(eGERR, "Erreur SQL : %s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr());
        return false;
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GMySQL::runRead() {
    try {
        if(!openDatabase()) return false;
        m_stmt.reset(m_con->createStatement());
        m_res.reset(m_stmt->executeQuery(m_sql.c_str()));
    }
    catch (sql::SQLException &e) {
        m_logs.addError("L'opération a rencontré un problème.");
        GLOGT(eGERR, "Erreur SQL : %s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr());
        return false;
    }
    return !m_logs.hasErrors();
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
        m_logs.addError("L'opération a rencontré un problème.");
        GLOGT(eGERR, "Erreur SQL : %s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr());
    }
    return lId;
}
//===============================================
GString GMySQL::readData(const GString& _sql) {
    GString lData;
    setSql(_sql);
    setAction("read");
    if(!run()) return lData;
    while(m_res->next()) {
        lData = m_res->getString(1);
        break;
    }
    return lData;
}
//===============================================
GMySQL::GRows GMySQL::readCol(const GString& _sql) {
    GMySQL::GRows lDataMap;
    setSql(_sql);
    setAction("read");
    if(!run()) return lDataMap;
    while(m_res->next()) {
        GString lData = m_res->getString(1).c_str();
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
GMySQL::GRows GMySQL::readRow(const GString& _sql) {
    GMySQL::GRows lDataMap;
    setSql(_sql);
    setAction("read");
    if(!run()) return lDataMap;
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
GMySQL::GMaps GMySQL::readMap(const GString& _sql) {
    GMySQL::GMaps lDataMap;
    setSql(_sql);
    setAction("read");
    if(!run()) return lDataMap;
    int lColumns = getColumnCount();
    while(m_res->next()) {
        GMySQL::GRows lDataRow;
        for(int i = 1; i <= lColumns; i++) {
            GString lData = m_res->getString(i).c_str();
            lDataRow.push_back(lData);
        }
        lDataMap.push_back(lDataRow);
    }
    return lDataMap;
}
//===============================================
