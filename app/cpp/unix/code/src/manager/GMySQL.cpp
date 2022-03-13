//===============================================
#include "GMySQL.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GMySQL::GMySQL() : GObject() {
    m_driver = 0;
    m_con = 0;
    m_stmt = 0;
    m_res = 0;
}
//===============================================
GMySQL::~GMySQL() {
    delete m_con;
}
//===============================================
GMySQL& GMySQL::openDatabase() {
    if(GLOGI->hasError()) return *this;
    m_driver = get_driver_instance();
    m_con = m_driver->connect("tcp://127.0.0.1:3306", "root", "root");
    return *this;
}
//===============================================
