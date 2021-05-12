//===============================================
#include "GDog.h"
//===============================================
static void GDog_Delete(GAnimalO* obj);
static void GDog_Print(GAnimalO* obj);
//===============================================
GAnimalO* GDog_New(int weight) {
    GAnimalO* lParent = GAnimal_New();
    GDogO* lChild = (GDogO*)malloc(sizeof(GDogO));

    lParent->child = lChild;
    lParent->Delete = GDog_Delete;
    lParent->Print = GDog_Print;
    return lParent;
}
//===============================================
static void GDog_Delete(GAnimalO* obj) {
    GAnimal_Delete(obj);
}
//===============================================
static void GDog_Print(GAnimalO* obj) {
    printf("Je suis un chien\n");
}
//===============================================
