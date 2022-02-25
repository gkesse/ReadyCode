//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMYSQL GMySQL::Instance()
//===============================================
class GMySQL : public GObject {
	Q_OBJECT

public:
    GMySQL(QObject* _parent = 0);
    ~GMySQL();
    static GMySQL* Instance();
    void open();

private:
    static GMySQL* m_instance;
    //
    sql::Driver* m_driver;
    sql::Connection* m_con;
    sql::Statement* m_stmt;
    sql::ResultSet* m_res;
};
//==============================================
#endif
//==============================================
