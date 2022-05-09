//===============================================
#include "GAnimal.h"
#include "GCat.h"
#include "GDog.h"
//===============================================
static void GAnimal_Print(GAnimalO* obj);
//===============================================
GAnimalO* GAnimal_New() {
    GAnimalO* lObj = (GAnimalO*)malloc(sizeof(GAnimalO));
    
    lObj->Delete = GAnimal_Delete;
    lObj->Print = GAnimal_Print;
    return lObj;
}
//===============================================
void GAnimal_Delete(GAnimalO* obj) {
    free(obj);
}
//===============================================
GAnimalO* GAnimal(const char* key) {
    if(!strcmp(key, "animal")) {return GAnimal_New();}
    if(!strcmp(key, "cat")) {return GCat_New();}
    if(!strcmp(key, "dog")) {return GDog_New();}
    return GAnimal_New();
}
//===============================================
static void GAnimal_Print(GAnimalO* obj) {
    printf("Je suis un animal\n");
}
//===============================================
