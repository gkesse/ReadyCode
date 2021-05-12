//===============================================
#ifndef _GDog_
#define _GDog_
//===============================================
#include "GAnimal.h"
//===============================================
typedef struct _GDogO GDogO;
//===============================================
struct _GDogO {
    void (*Delete)(GAnimalO* obj);
    void (*Print)(GAnimalO* obj);
};
//===============================================
GAnimalO* GDog_New();
//===============================================
#endif
//===============================================
