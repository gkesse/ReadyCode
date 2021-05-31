//===============================================
#ifndef _GDog_
#define _GDog_
//===============================================
#include "GAnimal.h"
//===============================================
class GDog : public GAnimal {
public:
    GDog(const std::string& name, int weight);
    ~GDog();

public:
    void print();
    
private:
    int m_weight;
};
//===============================================
#endif
//===============================================
