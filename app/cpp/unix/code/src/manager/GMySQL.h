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
    GMySQL& openDatabase(const std::string& _hostname, const std::string& _port, const std::string& _username, const std::string& _password);

private:
    sql::Driver* m_driver;
    sql::Connection* m_con;
    sql::Statement* m_stmt;
    sql::ResultSet* m_res;
};
//==============================================
#endif
//==============================================
