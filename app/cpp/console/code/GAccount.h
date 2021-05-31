//===============================================
#ifndef _GAccount_
#define _GAccount_
//===============================================
#include <iostream>
//===============================================
class GAccount {
public:
    GAccount(const std::string& name);
    ~GAccount();
    
public:
    void sayHello();

private:
    std::string m_name;
};
//===============================================
GAccount::GAccount(const std::string& name) {
    m_name = name;
}
//===============================================
GAccount::~GAccount() {

}
//===============================================
void GAccount::sayHello() {
    printf("Bonjour %s\n", m_name.c_str());
}
//===============================================
#endif
//===============================================
