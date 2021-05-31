//===============================================
#include "GCat.h"
//===============================================
GCat::GCat(const std::string& name, int price) :
GAnimal(name) {
    m_price = price;
}
//===============================================
GCat::~GCat() {
    
}
//===============================================
void GCat::print() {
    printf("[Cat] Nom : %s | Categorie : %s | Prix : %d (€)\n", 
    m_name.c_str(), m_category.c_str(), m_price);
}
//===============================================
