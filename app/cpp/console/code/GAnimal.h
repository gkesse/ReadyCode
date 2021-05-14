//===============================================
#ifndef _GAnimal_
#define _GAnimal_
//===============================================
#include <iostream>
#include <string>
//===============================================
class GAnimal {
public:
    GAnimal(const std::string& name, const int& code, const double& coef);
    ~GAnimal();

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
