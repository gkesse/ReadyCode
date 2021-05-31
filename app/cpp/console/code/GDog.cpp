//===============================================
#include "GDog.h"
//===============================================
GDog::GDog(const std::string& name, int weight) :
GAnimal(name) {
    m_weight = weight;
}
//===============================================
GDog::~GDog() {
    
}
//===============================================
void GDog::print() {
    printf("[Dog] Nom : %s | Categorie : %s | Poids : %d (kg)\n", 
    m_name.c_str(), m_category.c_str(), m_weight);
}
//===============================================
