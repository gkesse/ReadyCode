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
    GMySQL& openDatabase();

private:
    sql::Driver* m_driver;
    sql::Connection* m_con;
    sql::Statement* m_stmt;
    sql::ResultSet* m_res;
};
//==============================================
#endif
//==============================================
