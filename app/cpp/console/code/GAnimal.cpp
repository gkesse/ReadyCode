//===============================================
#include "GAnimal.h"
//===============================================
GAnimal::GAnimal(const std::string& name) {
    m_name = name;
}
//===============================================
GAnimal::~GAnimal() {
    
}
//===============================================
void GAnimal::setCategory(const std::string& category) {
    m_category = category;
}
//===============================================
