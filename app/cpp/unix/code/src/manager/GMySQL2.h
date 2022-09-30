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
    GString serialize(const GString& _code = "mysql") const;
    bool deserialize(const GString& _data, const GString& _code = "mysql");
    bool deserializeDom(const GString& _code = "mysql");
    //
    GString loadDatabase(bool _isTestEnv) const;
    //
    bool openDatabase();
    bool openDatabase(bool _isTestEnv);
    bool openDatabase(const GString& _protocol, const GString& _hostname, const GString& _port, const GString& _username, const GString& _password, const GString& _database);
    GMySQL2& execQuery(const GString& _sql);
    GMySQL2& execQuery(const GString& _sql, bool _isTestEnv);
    bool readQuery(const GString& _sql);
    bool readQuery(const GString& _sql, bool _isTestEnv);
    int getColumnCount() const;
    int getId();
    GString readData(const GString& _sql);
    GString readData(const GString& _sql, bool _isTestEnv);
    std::vector<GString> readCol(const GString& _sql);
    std::vector<GString> readCol(const GString& _sql, bool _isTestEnv);
    std::vector<GString> readRow(const GString& _sql);
    std::vector<GString> readRow(const GString& _sql, bool _isTestEnv);
    std::vector<std::vector<GString>> readMap(const GString& _sql);
    std::vector<std::vector<GString>> readMap(const GString& _sql, bool _isTestEnv);

private:
    sql::Driver* m_driver;
    std::shared_ptr<sql::Connection> m_con;
    std::shared_ptr<sql::Statement> m_stmt;
    std::shared_ptr<sql::ResultSet> m_res;
    //
    GString m_protocol;
    GString m_hostname;
    GString m_port;
    GString m_username;
    GString m_password;
    GString m_databaseTest;
    GString m_databaseProd;
};
//==============================================
#endif
//==============================================
