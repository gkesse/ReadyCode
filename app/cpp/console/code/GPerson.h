//===============================================
#ifndef _GPerson_
#define _GPerson_
//===============================================
#include <iostream>
#include <string>
//===============================================
class GPerson {
public:
    GPerson(const std::string& name, const int& code, const double& coef);
    ~GPerson();

public:
    void print();
    
private:
    std::string m_name;
    int m_code;
    double m_coef;
};
//===============================================
#endif
//===============================================
