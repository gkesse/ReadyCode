//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMYSQLI GMySQL::Instance()
//===============================================
class GMySQL : public GObject {
public:
    GMySQL();
    ~GMySQL();
    //
    std::string serialize(const std::string& _code = "mysql") const;
    void deserialize(const std::string& _data, const std::string& _code = "mysql");
    void deserializeDom(const std::string& _code = "mysql");
    //
    std::string loadDatabase(bool _isTestEnv) const;
    //
    bool openDatabase();
    bool openDatabase(bool _isTestEnv);
    bool openDatabase(const std::string& _protocol, const std::string& _hostname, const std::string& _port, const std::string& _username, const std::string& _password, const std::string& _database);
    GMySQL& execQuery(const std::string& _sql);
    GMySQL& execQuery(const std::string& _sql, bool _isTestEnv);
    bool readQuery(const std::string& _sql);
    bool readQuery(const std::string& _sql, bool _isTestEnv);
    int getColumnCount() const;
    int getId();
    std::string readData(const std::string& _sql);
    std::string readData(const std::string& _sql, bool _isTestEnv);
    std::vector<std::string> readCol(const std::string& _sql);
    std::vector<std::string> readCol(const std::string& _sql, bool _isTestEnv);
    std::vector<std::string> readRow(const std::string& _sql);
    std::vector<std::string> readRow(const std::string& _sql, bool _isTestEnv);
    std::vector<std::vector<std::string>> readMap(const std::string& _sql);
    std::vector<std::vector<std::string>> readMap(const std::string& _sql, bool _isTestEnv);

private:
    sql::Driver* m_driver;
    std::shared_ptr<sql::Connection> m_con;
    std::shared_ptr<sql::Statement> m_stmt;
    std::shared_ptr<sql::ResultSet> m_res;
    //
    std::string m_protocol;
    std::string m_hostname;
    std::string m_port;
    std::string m_username;
    std::string m_password;
    std::string m_databaseTest;
    std::string m_databaseProd;
};
//==============================================
#endif
//==============================================
