//===============================================
#include "GMySQL.h"
#include "GCode.h"
//===============================================
GMySQL* GMySQL::m_instance = 0;
//===============================================
GMySQL::GMySQL()
: GObject() {
    m_id = 0;
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
GString GMySQL::toDatabase() const {
    if(isTestEnv()) return "rdv_base_test_01";
    return "rdv_base_prod";
}
//===============================================
int GMySQL::getId() const {
    return m_id;
}
//===============================================
GString GMySQL::convertZeroToNull(int _data) {
    if(_data == 0) return "null";
    return _data;
}
//===============================================
int GMySQL::getColumnCount(std::shared_ptr<sql::ResultSet>& _resultSet) const {
    int lColumns = _resultSet->getMetaData()->getColumnCount();
    return lColumns;
}
//===============================================
bool GMySQL::openDatabase(std::shared_ptr<sql::Connection>& _conn) {
    GString lProtocol = "tcp";
    GString lHostname = "127.0.0.1";
    GString lDatabase = toDatabase();
    GString lUsername = "admin";
    GString lPassword = "xKCQY7GiGTVJ4l334QxN87@TKg";
    int lPort = 3306;

    try {
        sql::Driver* lDriver = get_driver_instance();

        if(!lDriver) {
            m_logs.addError("Le driver mysql n'est pas initialisé.");
            return false;
        }

        GString lPath = sformat("%s://%s:%d/%s"
                , lProtocol.c_str()
                , lHostname.c_str()
                , lPort
                , lDatabase.c_str()
        );

        _conn.reset(lDriver->connect(lPath.c_str(), lUsername.c_str(), lPassword.c_str()));
    }
    catch(sql::SQLException& e) {
        m_logs.addError("L'opération a rencontré un problème.");
        m_dataLogs.addError(sformat("Erreur SQL : %s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr()));
        return false;
    }
    return true;
}
//===============================================
bool GMySQL::execQuery(const GString& _sql) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::Statement> lStatement;

    try {
        if(!openDatabase(lConn)) return false;
        lStatement.reset(lConn->createStatement());
        lStatement->execute(_sql.c_str());
    }
    catch (sql::SQLException& e) {
        if(e.getErrorCode() == 1062) {
            m_logs.addError("Cette donnée existe déjà.");
        }
        else {
            m_logs.addError("L'opération a rencontré un problème.");
            m_dataLogs.addError(sformat("Erreur SQL : %s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr()));
        }
        return false;
    }
    return true;
}
//===============================================
bool GMySQL::insertQuery(const GString& _sql) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::Statement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;

    try {
        if(!openDatabase(lConn)) return false;
        lStatement.reset(lConn->createStatement());
        lStatement->execute(_sql.c_str());
        lResultSet.reset(lStatement->executeQuery("select @@identity as id"));
        lResultSet->next();
        m_id = (int)lResultSet->getInt64("id");
    }
    catch (sql::SQLException& e) {
        if(e.getErrorCode() == 1062) {
            m_logs.addError("Cette donnée existe déjà.");
        }
        else {
            m_logs.addError("L'opération a rencontré un problème.");
            m_dataLogs.addError(sformat("Erreur SQL : %s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr()));
        }
        return false;
    }
    return true;
}
//===============================================
bool GMySQL::readQuery(const GString& _sql, std::shared_ptr<sql::ResultSet>& _resultSet) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::Statement> lStatement;

    try {
        if(!openDatabase(lConn)) return false;
        lStatement.reset(lConn->createStatement());
        _resultSet.reset(lStatement->executeQuery(_sql.c_str()));
    }
    catch (sql::SQLException &e) {
        m_logs.addError("L'opération a rencontré un problème.");
        m_dataLogs.addError(sformat("Erreur SQL : %s : %d : %s", e.what(), e.getErrorCode(), e.getSQLStateCStr()));
        return false;
    }
    return true;
}
//===============================================
GString GMySQL::readData(const GString& _sql) {
    GString lData;
    std::shared_ptr<sql::ResultSet> lResultSet;
    if(!readQuery(_sql, lResultSet)) return "";
    while(lResultSet->next()) {
        lData = lResultSet->getString(1);
        break;
    }
    return lData;
}
//===============================================
GMySQL::GRows GMySQL::readCol(const GString& _sql) {
    GMySQL::GRows lDataMap;
    std::shared_ptr<sql::ResultSet> lResultSet;
    if(!readQuery(_sql, lResultSet)) return lDataMap;
    while(lResultSet->next()) {
        GString lData = lResultSet->getString(1).c_str();
        lDataMap.push_back(lData);
    }
    return lDataMap;
}
//===============================================
GMySQL::GRows GMySQL::readRow(const GString& _sql) {
    GMySQL::GRows lDataMap;
    std::shared_ptr<sql::ResultSet> lResultSet;
    if(!readQuery(_sql, lResultSet)) return lDataMap;
    int lColumns = getColumnCount(lResultSet);
    while(lResultSet->next()) {
        for(int i = 1; i <= lColumns; i++) {
            GString lData = lResultSet->getString(i).c_str();
            lDataMap.push_back(lData);
        }
        break;
    }
    return lDataMap;
}
//===============================================
GMySQL::GMaps GMySQL::readMap(const GString& _sql) {
    GMySQL::GMaps lDataMap;
    std::shared_ptr<sql::ResultSet> lResultSet;
    if(!readQuery(_sql, lResultSet)) return lDataMap;
    int lColumns = getColumnCount(lResultSet);
    while(lResultSet->next()) {
        GMySQL::GRows lDataRow;
        for(int i = 1; i <= lColumns; i++) {
            GString lData = lResultSet->getString(i).c_str();
            lDataRow.push_back(lData);
        }
        lDataMap.push_back(lDataRow);
    }
    return lDataMap;
}
//===============================================
