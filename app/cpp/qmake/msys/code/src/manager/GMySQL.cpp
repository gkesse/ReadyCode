//===============================================
#include "GMySQL.h"
//===============================================
GMySQL* GMySQL::m_instance = 0;
//===============================================
GMySQL::GMySQL(QObject* _parent) :
GObject(_parent) {
	m_driver = 0;
	m_con = 0;
	m_stmt = 0;
	m_res = 0;
}
//===============================================
GMySQL::~GMySQL() {

}
//===============================================
GMySQL* GMySQL::Instance() {
    if(m_instance == 0) {
        m_instance = new GMySQL;
    }
    return m_instance;
}
//===============================================
void GMySQL::open() {
	  m_driver = get_driver_instance();
	  m_con = m_driver->connect("tcp://127.0.0.1:3306", "root", "root");
	  m_con->setSchema("test");
	  m_stmt = m_con->createStatement();
}
//===============================================
