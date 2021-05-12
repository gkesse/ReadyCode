//===============================================
#ifndef _GAnimal_
#define _GAnimal_
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//===============================================
typedef struct _GAnimalO GAnimalO;
//===============================================
struct _GAnimalO {
    void* child;
    void (*Delete)(GAnimalO* obj);
    void (*Print)(GAnimalO* obj);
};
//===============================================
GAnimalO* GAnimal(const char* key);
GAnimalO* GAnimal_New();
void GAnimal_Delete(GAnimalO* obj);
//===============================================
#endif
//===============================================
