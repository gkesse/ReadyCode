//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMySQLI     GMySQL::Instance()
//===============================================
typedef std::vector<std::vector<GString>> GMaps;
typedef std::vector<GString> GRow;
//===============================================
class GMySQL : public GObject {
public:
    GMySQL(const GString& _code = "mysql");
    ~GMySQL();

    void initMySQL();

    bool openDatabase();
    bool execQuery(const GString& _sql);
    bool readQuery(const GString& _sql);
    int getColumnCount() const;
    int getId();
    GString readData(const GString& _sql);
    std::vector<GString> readCol(const GString& _sql);
    std::vector<GString> readRow(const GString& _sql);
    std::vector<std::vector<GString>> readMap(const GString& _sql);

private:
    sql::Driver* m_driver;
    std::shared_ptr<sql::Connection> m_con;
    std::shared_ptr<sql::Statement> m_stmt;
    std::shared_ptr<sql::ResultSet> m_res;

    bool m_isTestEnv;

    GString m_protocol;
    GString m_hostname;
    GString m_username;
    GString m_password;
    GString m_database;
    int m_port;

    GString m_databaseTest;
    GString m_databaseProd;
    bool m_logOn;
};
//==============================================
#endif
//==============================================
