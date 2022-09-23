//===============================================
#ifndef _GMySQL2_
#define _GMySQL2_
//===============================================
#include "GObject2.h"
//===============================================
#define GMySQL2I GMySQL2::Instance()
//===============================================
class GMySQL2 : public GObject2 {
public:
    GMySQL2();
    ~GMySQL2();
    //
    GString2 serialize(const GString2& _code = "mysql") const;
    bool deserialize(const GString2& _data, const GString2& _code = "mysql");
    bool deserializeDom(const GString2& _code = "mysql");
    //
    GString2 loadDatabase(bool _isTestEnv) const;
    //
    bool openDatabase();
    bool openDatabase(bool _isTestEnv);
    bool openDatabase(const GString2& _protocol, const GString2& _hostname, const GString2& _port, const GString2& _username, const GString2& _password, const GString2& _database);
    GMySQL2& execQuery(const GString2& _sql);
    GMySQL2& execQuery(const GString2& _sql, bool _isTestEnv);
    bool readQuery(const GString2& _sql);
    bool readQuery(const GString2& _sql, bool _isTestEnv);
    int getColumnCount() const;
    int getId();
    GString2 readData(const GString2& _sql);
    GString2 readData(const GString2& _sql, bool _isTestEnv);
    std::vector<GString2> readCol(const GString2& _sql);
    std::vector<GString2> readCol(const GString2& _sql, bool _isTestEnv);
    std::vector<GString2> readRow(const GString2& _sql);
    std::vector<GString2> readRow(const GString2& _sql, bool _isTestEnv);
    std::vector<std::vector<GString2>> readMap(const GString2& _sql);
    std::vector<std::vector<GString2>> readMap(const GString2& _sql, bool _isTestEnv);

private:
    sql::Driver* m_driver;
    std::shared_ptr<sql::Connection> m_con;
    std::shared_ptr<sql::Statement> m_stmt;
    std::shared_ptr<sql::ResultSet> m_res;
    //
    GString2 m_protocol;
    GString2 m_hostname;
    GString2 m_port;
    GString2 m_username;
    GString2 m_password;
    GString2 m_databaseTest;
    GString2 m_databaseProd;
};
//==============================================
#endif
//==============================================
