//===============================================
#ifndef _GCat_
#define _GCat_
//===============================================
#include "GAnimal.h"
//===============================================
class GCat : public GAnimal {
public:
    GCat(const std::string& name, int price);
    ~GCat();

public:
    void print();
    
private:
    int m_price;
};
//===============================================
#endif
//===============================================
