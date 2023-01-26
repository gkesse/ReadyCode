//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMYSQL      GMySQL::Instance()
#define czton       GMYSQL->convertZeroToNull
//===============================================
typedef std::vector<GString> GRows;
typedef std::vector<GRows> GMaps;
//===============================================
class GMySQL : public GObject {
public:
    GMySQL();
    ~GMySQL();
    static GMySQL* Instance();
    void initMySQL();
    void setAction(const GString& _action);
    void setSql(const GString& _sql);
    GString convertZeroToNull(int _data);
    bool openDatabase();
    bool execQuery(const GString& _sql);
    bool run();
    bool runWrite();
    bool runRead();
    int getColumnCount() const;
    int getId();
    GString readData(const GString& _sql);
    GRows readCol(const GString& _sql);
    GRows readRow(const GString& _sql);
    GMaps readMap(const GString& _sql);

private:
    static GMySQL* m_instance;
    sql::Driver* m_driver;
    std::shared_ptr<sql::Connection> m_con;
    std::shared_ptr<sql::Statement> m_stmt;
    std::shared_ptr<sql::ResultSet> m_res;

    GString m_action;
    GString m_sql;
    GString m_protocol;
    GString m_hostname;
    GString m_username;
    GString m_password;
    GString m_database;
    int m_port;
};
//==============================================
#endif
//==============================================
