//===============================================
#include "GButton.h"
//===============================================
static void GButton_Delete(GWidgetO* obj);
static void GButton_Click(GWidgetO* obj);
//===============================================
GWidgetO* GButton_New() {
    GWidgetO* lParent = GWidget_New();
    GButtonO* lChild = (GButtonO*)malloc(sizeof(GButtonO));

    lParent->child = lChild;
    lParent->Delete = GButton_Delete;
    lParent->Click = GButton_Click;
    return lParent;
}
//===============================================
static void GButton_Delete(GWidgetO* obj) {
    GWidget_Delete(obj);
}
//===============================================
static void GButton_Click(GWidgetO* obj) {
    printf("Je clique sur le BOUTON\n");
    obj->EmitClick(obj);
}
//===============================================
