//===============================================
#include "GError.h"
//===============================================
GError::GError(int num, const std::string& msg, int level) throw() {
    m_num = num;
    m_msg = msg;
    m_level = level;
}
//===============================================
GError::~GError() throw() {
    
}
//===============================================
const char* GError::what() const throw() {
    return m_msg.c_str();
}
//===============================================
