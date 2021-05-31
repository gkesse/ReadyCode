//===============================================
#ifndef _GError_
#define _GError_
//===============================================
#include <iostream>
#include <string>
#include <exception>
//===============================================
class GError : public std::exception {
public:
    GError(int num, const std::string& msg, int level) throw();
    ~GError() throw();

public:
    const char* what() const throw();

private:
    int m_num;
    std::string m_msg;
    int m_level;
};
//===============================================
#endif
//===============================================
