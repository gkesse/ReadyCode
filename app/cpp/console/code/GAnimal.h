//===============================================
#ifndef _GAnimal_
#define _GAnimal_
//===============================================
#include <iostream>
#include <string>
//===============================================
class GAnimal {
public:
    GAnimal(const std::string& name);
    virtual ~GAnimal();

public:
    virtual void setCategory(const std::string& category);
    virtual void print() = 0;
    
protected:
    std::string m_name;
    std::string m_category;
};
//===============================================
#endif
//===============================================
