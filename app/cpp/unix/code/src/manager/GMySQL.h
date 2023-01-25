//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
typedef std::vector<std::vector<GString>> GMaps;
typedef std::vector<GString> GRow;
//===============================================
class GMySQL : public GObject {
public:
    GMySQL();
    ~GMySQL();
    void initMySQL();
    void setAction(const GString& _action);
    void setSql(const GString& _sql);
    bool openDatabase();
    bool execQuery(const GString& _sql);
    bool run();
    bool runWrite();
    bool runRead();
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
