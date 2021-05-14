//===============================================
#include "GAnimal.h"
//===============================================
GAnimal::GAnimal(const std::string& name, const int& code, const double& coef) {
    m_name = name;
    m_code = code;
    m_coef = coef;
}
//===============================================
GAnimal::~GAnimal() {
    
}
//===============================================
void GAnimal::print() {
    printf("Personne[name] : %s\n", m_name.c_str());
    printf("Personne[code] : %d\n", m_code);
    printf("Personne[coef] : %.2f\n", m_coef);
}
//===============================================
