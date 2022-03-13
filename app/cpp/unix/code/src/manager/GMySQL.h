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
    void createDoms();
    //
    GMySQL& openDatabase();
    GMySQL& openDatabase(const std::string& _protocol, const std::string& _hostname, const std::string& _port, const std::string& _username, const std::string& _password, const std::string& _database);
    GMySQL& execQuery(const std::string& _sql);
    std::string readData(const std::string& _sql);

private:
    sql::Driver* m_driver;
    std::shared_ptr<sql::Connection> m_con;
    std::shared_ptr<sql::Statement> m_stmt;
    std::shared_ptr<sql::ResultSet> m_res;
};
//==============================================
#endif
//==============================================
