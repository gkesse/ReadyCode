//===============================================
#include "GCat.h"
//===============================================
static void GCat_Delete(GAnimalO* obj);
static void GCat_Print(GAnimalO* obj);
//===============================================
GAnimalO* GCat_New() {
    GAnimalO* lParent = GAnimal_New();
    GCatO* lChild = (GCatO*)malloc(sizeof(GCatO));

    lParent->child = lChild;
    lParent->Delete = GCat_Delete;
    lParent->Print = GCat_Print;
    return lParent;
}
//===============================================
static void GCat_Delete(GAnimalO* obj) {
    GAnimal_Delete(obj);
}
//===============================================
static void GCat_Print(GAnimalO* obj) {
    printf("Je suis un chat\n");
}
//===============================================
